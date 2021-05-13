#include <uranos/pfalloc.h>
#include <uranos/bitmap.h>
#include <uranos/heap.h>

#include <uranos/kernel.h>    // kprintf

/*
typedef struct heap_block {
  struct heap_block* prev;
  struct heap_block* next;
  size_t block_size;
  size_t bytemap_size;
  size_t size_bytes;
  size_t used_bytes;
  size_t free_bytes;
  size_t last_freed_offset;
} heap_block_t;
*/


/*
 * for the future we should have separate heaps for every userspace program,
 * so that garbage collection becomes possible
 */
static heap_block_t* kernel_heap;

#define DEFAULT_BLOCK_SIZE 32


void init_heap(void)
{
  /* NULLify heap */
  kernel_heap = NULL;

  /* Add a new block to the heap to start with */
  kernel_heap = create_heap_block(0x100000, DEFAULT_BLOCK_SIZE);
  return;
}

int add_heap_block(heap_block_t* alloc_heap, size_t size_bytes, size_t block_size)
{
  heap_block_t* new_block = create_heap_block(size_bytes, block_size);

  if(new_block == NULL)
    return -1;

  /* If the heap is empty, return fail */
  if(!alloc_heap)
  {
    return -1;
  }

  /* Otherwise add the newly allocated block to the (global) heap */
  heap_block_t* curr = alloc_heap;
  while(curr->next)
  {
    curr = curr->next;
  }
  new_block->prev = curr;
  curr->next = new_block;
  return 0;
}

heap_block_t* create_heap_block(size_t size_bytes, size_t block_size)
{
  /* Get the bytemap size */
  size_t bytemap_size = size_bytes / block_size;
  if(size_bytes % block_size)
    bytemap_size++;

  /* Allocate a block with at least size_bytes of allocatable mem */
  size_t pages = (size_bytes + bytemap_size + sizeof(heap_block_t)) / PAGE_SIZE;
  if((size_bytes + bytemap_size + sizeof(heap_block_t)) % PAGE_SIZE)
    pages++;

  kprintf("Allocating a new heap block with pfalloc (%d pages)!\n", pages);
  heap_block_t* block = (heap_block_t*)pfalloc_pages(pages);

  kprintf("Setting up the block ...");

  // TODO: virtual memory!
  

  /* Setup the block */
  block->prev = NULL;
  block->next = NULL;
  block->block_size = block_size;
  block->bytemap_size = bytemap_size;
  block->size_bytes = size_bytes;
  block->used_bytes = 0;
  block->free_bytes = size_bytes;
  block->last_freed_offset = 0;

  kprintf("New block allocated! size: %d, start: %x\n", block->size_bytes, block + sizeof(heap_block_t) + block->bytemap_size);

  /* Setup the bytemap */
  uint8_t* bytemap = (uint8_t*)&block[1];
  for(int i = 0; i < bytemap_size; i++)
  {
    bytemap[i] = 0;
  }

  return block;
}


uintptr_t malloc_from_block(heap_block_t* block, size_t size)
{
  if(block->free_bytes < size)
    return (uintptr_t)NULL;

  // Try to find free memory for allocation
  uint8_t* bytemap = (uint8_t*)&block[1];
  size_t needed_blocks = size / block->block_size;
  if(size % block->block_size)
    needed_blocks++;

  for(int i = block->last_freed_offset, iterated = 0; i < block->bytemap_size; i + iterated)
  {
    for(iterated = 0; bytemap[i+iterated] == 0 && i+iterated < block->bytemap_size; iterated++)
    {
      if(iterated == needed_blocks - 1)
      {
        uint8_t allocation_id = 0;
        /* Woohoo, we found free memory!! Now mark it allocated */
        /* If it is the first byte in the map only check right boundary */
        if(i == 0)
        {
          for(allocation_id = 0; allocation_id == bytemap[i+iterated+1] || allocation_id == 0; allocation_id++);
        }
        /* Else if the last block to be allocated is the last bitmap element only check left boundary */
        else if(i+iterated == block->bytemap_size-1)
        {
          for(allocation_id = bytemap[i-1] + 1; allocation_id == bytemap[i-1] || allocation_id == 0; allocation_id++);
        }
        /* Generic marking */
        else
        {
          for(allocation_id = bytemap[i-1] + 1; allocation_id == bytemap[i-1] || allocation_id == 0 || allocation_id == bytemap[i+iterated+1]; allocation_id++);
        }

        /* Now that we've found a free allocation ID, we will mark the needed blocks with said ID */
        for(int j = 0; j < needed_blocks; j++)
        {
          bytemap[i+j] = allocation_id;
        }

        /* Update the heap block header */
        block->used_bytes += needed_blocks * block->block_size;
        block->free_bytes -= needed_blocks * block->block_size;
        block->last_freed_offset = i + iterated + 1;

        return (uintptr_t)(bytemap + block->bytemap_size + (i * block->block_size));
      }
    }
  }

  /* If we could not find free memory from the last freed offset, wrap the block around */
  for(int i = 0, iterated = 0; i < block->bytemap_size; i + iterated)
  {
    for(iterated = 0; bytemap[i+iterated] == 0 && i+iterated < block->bytemap_size; iterated++)
    {
      if(iterated == needed_blocks - 1)
      {
        uint8_t allocation_id = 0;
        /* Woohoo, we found free memory!! Now mark it allocated */
        /* If it is the first byte in the map only check right boundary */
        if(i == 0)
        {
          for(allocation_id = 0; allocation_id == bytemap[i+iterated+1] || allocation_id == 0; allocation_id++);
        }
        /* Else if the last block to be allocated is the last bitmap element only check left boundary */
        else if(i+iterated == block->bytemap_size-1)
        {
          for(allocation_id = bytemap[i-1] + 1; allocation_id == bytemap[i-1] || allocation_id == 0; allocation_id++);
        }
        /* Generic marking */
        else
        {
          for(allocation_id = bytemap[i-1] + 1; allocation_id == bytemap[i-1] || allocation_id == 0 || allocation_id == bytemap[i+iterated+1]; allocation_id++);
        }

        /* Now that we've found a free allocation ID, we will mark the needed blocks with said ID */
        for(int j = 0; j < needed_blocks; j++)
        {
          bytemap[i+j] = allocation_id;
        }

        /* Update the heap block header */
        block->used_bytes += needed_blocks * block->block_size;
        block->free_bytes -= needed_blocks * block->block_size;
        block->last_freed_offset = i + iterated + 1;

        return (uintptr_t)(bytemap + block->bytemap_size + (i * block->block_size));
      }
    }
  }

  return (uintptr_t)NULL;
}

uintptr_t malloc_from_heap(heap_block_t* alloc_heap, size_t size)
{
  if(!alloc_heap)
  {
    (uintptr_t)NULL;
  }

  /* Try to find a block with enough memory for allocation */
  for(heap_block_t* curr = alloc_heap; curr; curr = curr->next)
  {
    if(curr->free_bytes >= size)
    {
      uintptr_t alloced = malloc_from_block(curr, size);
      if(alloced != (uintptr_t)NULL)
      {
        kprintf("malloc allocated memory from %x!\n", alloced);
        return alloced;
      }
    }
  }

  /* 
   * If we could not find a block with enough allocatable mem,
   * we will create a new block with enough space.
   * If the requested memory size is over 10 MiB, we allocate 
   * only memory needed for it, if under,
   * we allocate 4* the requested memory for future allocations
   */
  heap_block_t* new_block;
  if(size > 0x100000)
  {
    if(add_heap_block(alloc_heap, size, DEFAULT_BLOCK_SIZE))
    {
      return (uintptr_t)NULL;
    }
  }

  if(add_heap_block(alloc_heap, size * 4, DEFAULT_BLOCK_SIZE))
  {
    return (uintptr_t)NULL;
  }

  /* Try to find a block with enough memory for allocation (again) */
  for(heap_block_t* curr = alloc_heap; curr; curr = curr->next)
  {
    if(curr->free_bytes >= size)
    {
      uintptr_t alloced = malloc_from_block(curr, size);
      if(alloced != (uintptr_t)NULL) return alloced;
    }
  }

  /* If we could not allocate memory, bail out */
  return (uintptr_t)NULL;
}

uintptr_t kmalloc(size_t size)
{
  return malloc_from_heap(kernel_heap, size);
}

void kfree(uintptr_t addr)
{
  for(heap_block_t* block = kernel_heap; block; block = block->next)
  {
    if(addr > (uintptr_t)block && addr < (uintptr_t)block + sizeof(heap_block_t) + block->bytemap_size + block->size_bytes)
    {
      uintptr_t offset = addr - (uintptr_t)&block[1];
      int blidx = offset / block->block_size;
      uint8_t* bytemap = (uint8_t*)&block[1];
      uint8_t free_id = bytemap[blidx];
      for(;blidx < block->bytemap_size && bytemap[blidx] == free_id; blidx++)
      {
        bytemap[blidx] = 0;
      }
      return;
    }
  }
  return;
}