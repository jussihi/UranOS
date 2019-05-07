#ifndef __URANOS_ARCH_HH
#define __URANOS_ARCH_HH

#ifdef __URANOS_ARCH_x86__

#include <tss.h>
#include <hal.h>
#include <gdt.h>
#include <idt.h>
#include <pit.h>

#endif

void init_arch(void);

#endif /* __URANOS_ARCH_H */