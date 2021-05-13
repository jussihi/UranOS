#ifndef __URANOS_X86_IDT_H
#define __URANOS_X86_IDT_H

#include <x86.h>

#define IDT_INTERRUPT_COUNT 256
#define IDT_GATE_TYPE_INTR 0xE
#define IDT_GATE_TYPE_TRAP 0xF

typedef struct __attribute__((__packed__)) {
  uint16_t offset_lo;
  uint16_t selector;
  uint8_t zero_byte;
  uint8_t type_attr;
  uint16_t offset_hi;
} IDT_t;

typedef void interrupt_handler (pt_regs*);


int interrupt_register_handler(interrupt_handler* handler, int intno, int dpl, int level);

void interrupt_relay(pt_regs* ctx);

void idt_set_gate(int idx, uint32_t handler, uint8_t type, uint8_t dpl);

void idt_init();

#endif /* __URANOS_X86_IDT_H */