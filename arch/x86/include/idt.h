#ifndef __URANOS_X86_IDT_H
#define __URANOS_X86_IDT_H

#include <cpu.h>

void idt_init();

void interrupt_relay(interrupt_ctx* ctx);

#endif /* __URANOS_X86_IDT_H */