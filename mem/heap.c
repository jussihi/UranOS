#include <uranos/pfalloc.h>
#include <uranos/bitmap.h>
#include <uranos/heap.h>

/*
typedef struct heap_block {
  struct heap_block* prev;
  struct heap_block* next;
  size_t block_size;
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
static heap_block_t* heap;


void init_heap(void)
{
  /* NULLify heap */
  heap = NULL;

  /* Add a new block to the heap to start with */
  add_heap_block(0x100000, 16);
  return;
}

int add_heap_block(size_t size_bytes, size_t block_size)
{
  heap_block_t* new_block = create_heap_block(size_bytes, block_size);

  if(new_block == NULL)
    return -1;

  /* If the heap is empty, point (global) heap to the newly allocated block */
  if(!heap)
  {
    heap = new_block;
    return 0;
  }

  /* Otherwise add the newly allocated block to the (global) heap */
  heap_block_t* curr = heap;
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
  /* Get the wordmap size */
  size_t wordmap_size = size_bytes / block_size;
  if(size_bytes % block_size)
    wordmap_size++;
  size_t wordmap_size_bytes = wordmap_size * sizeof(uint16_t);

  /* Allocate a block with at least size_bytes of allocatable mem */
  size_t pages = (size_bytes + wordmap_size_bytes + sizeof(heap_block_t)) / PAGE_SIZE;
  if((size_bytes + wordmap_size_bytes + sizeof(heap_block_t)) % PAGE_SIZE)
    pages++;
  heap_block_t* block = (heap_block_t*)pfalloc_pages(pages);

  /* Setup the block */
  block->prev = NULL;
  block->next = NULL;
  block->block_size = block_size;
  block->wordmap_size = wordmap_size;
  block->size_bytes = size_bytes;
  block->used_bytes = 0;
  block->free_bytes = size_bytes;
  block->last_freed_offset = 0;

  /* Setup the wordmap */
  uint16_t* wordmap = (uint16_t*)&block[1];
  for(int i = 0; i < wordmap_size; i++)
  {
    wordmap[i] = 0;
  }

  return block;
}

uintptr_t kmalloc_from_block(heap_block_t* block, size_t size)
{
  // TODO: IMPLEMENT!
  return (uintptr_t)NULL;
}

uintptr_t kmalloc(size_t size)
{
  // TODO: IMPLEMENT!
  return (uintptr_t)NULL;
}

void kfree(uintptr_t addr)
{
  // TODO: IMPLEMENT!
  return;
}