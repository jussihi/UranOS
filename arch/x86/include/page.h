#ifndef __URANOS_X86_PAGE_H
#define __URANOS_X86_PAGE_H

#include <stdint.h>


/* Define the physical memory boundaries for paging */

#define KERNEL_PHYS_START 0x00100000
#define KERNEL_VIRT_START 0xC0100000

#define VIRT_START 0xC0000000

#define PAGE_SIZE 4096


#define PTE_PRESENT_SHIFT   0
#define PTE_RW_SHIFT        1
#define PTE_USER_SHIFT      2
#define PTE_WRITETHRU_SHIFT 3
#define PTE_CACHE_SHIFT     4
#define PTE_ACCESS_SHIFT    5
#define PTE_DIRTY_SHIFT     6
#define PTE_ZERO_SHIFT      7
#define PTE_ZERO_MASK       (~(1 << PTE_ZERO_SHIFT))
#define PTE_GLOB_SHIFT      8
#define PTE_COW_SHIFT       9
#define PTE_AVAIL_MASK      (~((1 << 9) | (1 << 10) | (1 << 11)))
#define PTE_ADDR_SHIFT      12

#define PDE_PRESENT_SHIFT   0
#define PDE_RW_SHIFT        1
#define PDE_USER_SHIFT      2
#define PDE_WRITETHRU_SHIFT 3
#define PDE_CACHE_SHIFT     4
#define PDE_ACCESS_SHIFT    5
#define PDE_ZERO_SHIFT      6
#define PDE_ZERO_MASK       (~(1 << PTE_ZERO_SHIFT))
#define PDE_SIZE_SHIFT      7
#define PDE_IGNORE_SHIFT    8
#define PDE_COW_SHIFT       9
#define PDE_AVAIL_MASK      (~((1 << 9) | (1 << 10) | (1 << 11)))
#define PDE_ADDR_SHIFT      12

#define PG_P_USER     1
#define PG_P_KERN     0

#define PG_R_RO       0
#define PG_R_RW       1

// page table entry     = page entry
// page directory entry = page table
typedef uint32_t     pte_t;
typedef uint32_t     pde_t;


void reinit_paging();

#endif