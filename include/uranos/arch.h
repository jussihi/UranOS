#ifndef __URANOS_ARCH_HH
#define __URANOS_ARCH_HH

#include <stdint.h>

#ifdef __URANOS_ARCH_x86__

#include <tss.h>
#include <hal.h>
#include <gdt.h>
#include <idt.h>
#include <pit.h>

typedef uint32_t bm_element;

#define MAX_PAGE_FRAMES 32768 // 4 GiB

#define BITS_PER_LONG 32
#define LONG_MAX_VALUE 4294967295

#endif

void init_arch(void);

#endif /* __URANOS_ARCH_H */