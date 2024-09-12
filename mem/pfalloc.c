#include <uranos/pfalloc.h>
#include <uranos/bitmap.h>

#include <uranos/kernel.h>

// These come from arch, because arch-based (if we ever get to 64-bit lol)
// Because one page is 4096 bytes, we must use 32768*32 (sizeof bm_element) to get total of 
// 4 GiB
static bm_element pfalloc_bitmap[MAX_PAGE_FRAMES];
static bitmap_t pfalloc_bm;


void pfalloc_mark_addr(uintptr_t addr)
{
    bm_set_bit_on(&pfalloc_bm, addr / PAGE_SIZE);
}

static void pfalloc_mark_idx(uint32_t idx)
{
    bm_set_bit_on(&pfalloc_bm, idx);
}

uintptr_t pfalloc_pages(int num_pages)
{
    int32_t idx;
    idx = bm_scan(&pfalloc_bm, 0, num_pages);

    if(idx == -1)
    {
        // out of memory!
        kprintf("pfalloc: no memory!\n");
        return (uintptr_t)NULL;
    }

    for(int i = idx; i < idx + num_pages; i++)
    {
        bm_set_bit_on(&pfalloc_bm, i);
    }
    return idx * 4096;
}

uintptr_t pfalloc_page(void)
{
    return pfalloc_pages(1);
}

void pfalloc_init(void)
{
    //TODO: Get the RAM amount somehow
    pfalloc_bm.bit_count = MAX_PAGE_FRAMES - 1;
    pfalloc_bm.bits = pfalloc_bitmap;
    bm_set_all(&pfalloc_bm, 0);

    // mark the first 16 MiB
    for(uintptr_t addr = 0; addr < 16 * 1024 * 1024; addr += 4096)
    {
        pfalloc_mark_addr(addr);
    }

    // mark VGA memory
    for(uintptr_t addr = 0xB8000; addr <= 0xB8000 + 0xC0000; addr += 4096)
    {
        pfalloc_mark_addr(addr);
    }

    // Todo: mark kernel. How?

    return;
}