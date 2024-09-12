#ifndef __URANOS_ARCH_HH
#define __URANOS_ARCH_HH

#include <stdint.h>

#ifdef __URANOS_ARCH_i686__

#include <tss.h>
#include <hal.h>
#include <gdt.h>
#include <idt.h>
#include <pit.h>
#include <page.h>
#include <i686.h>

typedef uint32_t bm_element;



#endif

void init_arch(void);

#endif /* __URANOS_ARCH_H */