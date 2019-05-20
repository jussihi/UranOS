#include <uranos/pfalloc.h>
#include <uranos/bitmap.h>

// These come from arch, because arch-based (if we ever get to 64-bit lol)
// Because one page is 4096 bytes, we must use 32768*32 (sizeof bm_element) to get total of 
// 4 GiB
static bm_element pfalloc_bitmap[MAX_PAGE_FRAMES];
static bitmap_t pfalloc_bm;

void pfalloc_init(void)
{
	//TODO: Get the RAM amount somehow
	pfalloc_bm.bit_count = MAX_PAGE_FRAMES - 1;
	pfalloc_bm.bits = pfalloc_bitmap;
	bm_set_all(&pfalloc_bm, 0);


	//TODO: mark the kernel location, kernel space and VGA as used memory!

	return;
}