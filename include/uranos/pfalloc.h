#ifndef __URANOS_PFALLOC_HH
#define __URANOS_PFALLOC_HH

#include <uranos/arch.h>

void pfalloc_mark_addr(uintptr_t address);

uintptr_t pfalloc_pages(int num_pages);

uintptr_t pfalloc_page(void);

void pfalloc_init(void);


#endif /* __URANOS_PFALLOC_HH */