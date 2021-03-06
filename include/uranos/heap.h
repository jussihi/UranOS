#ifndef __URANOS_HEAP_HH
#define __URANOS_HEAP_HH

#include <uranos/arch.h>
#include <stddef.h>


typedef struct heap_block {
  struct heap_block* prev;
  struct heap_block* next;
  size_t block_size;
  size_t bytemap_size;
  size_t size_bytes;
  size_t used_bytes;
  size_t free_bytes;
  size_t last_freed_offset;
  uint8_t last_used_id;
} heap_block_t;


void init_heap(void);

/*
 * This function will _add_ AT LEAST the size of the requested size 
 * to the heap, meaning that the allocatable memory size is guaranteed 
 * to be at least "size_bytes"
 * 
 * Calls add_heap_block to create the new block
 */
int add_heap_block(heap_block_t* heap, size_t size_bytes, size_t block_size);

/*
 * This function will _create a heap block_ of AT LEAST the size of 
 * the requested size, meaning that the allocatable memory size is 
 * guaranteed to be at least "size_bytes"
 */
heap_block_t* create_heap_block(size_t size_bytes, size_t block_size);

/*
 * Allocates *size* amount of bytes of memory from a heap
 * block specified as a param
 */
uintptr_t malloc_from_block(heap_block_t* block, size_t size);

/*
 * Finds and allocates memory of amount of *size* bytes from
 * *alloc_heap*. This can be used for both kernel allocations (using kmalloc)
 * and userspace allocations, when ring3 app context has its own heap.
 *
 * Calls *malloc_from_block* to mark the heap wordmap
 * for the allocation
 */
uintptr_t malloc_from_heap(heap_block_t* alloc_heap, size_t size);

/*
 * Finds and allocates memory of amount of *size* bytes.
 *
 * Calls *malloc_from_heap* to alloc from kernel heap
 * for the allocation
 */
uintptr_t kmalloc(size_t size);

/*
 * Frees a given memory allocation from the heap
 */
void kfree(uintptr_t addr);


#endif