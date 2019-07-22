#include <idt.h>
#include <stdint.h>
#include <pic.h>
#include <uranos/string.h>
#include <uranos/kernel.h>

// This is from interrupt_trampoline.asm
// function pointers to the asm functions
extern uint32_t interrupt_fpointers[IDT_INTERRUPT_COUNT];

// the IDT table
static IDT_t idt[IDT_INTERRUPT_COUNT];

// handlers for the interrupts
static interrupt_handler *interrupt_handlers[IDT_INTERRUPT_COUNT];

int interrupt_register_handler(interrupt_handler* handler, int intno, int dpl, int level)
{
	if(intno < 0 || intno > 255)
	{
		return -1;
	}
	if(level == 1)
	{
		idt_set_gate(intno, interrupt_fpointers[intno], IDT_GATE_TYPE_TRAP, dpl);
	}
	else
	{
		idt_set_gate(intno, interrupt_fpointers[intno], IDT_GATE_TYPE_INTR, dpl);
	}
	interrupt_handlers[intno] = handler;
	return 0;
}


void interrupt_relay(pt_regs* ctx)
{
	if(interrupt_handlers[ctx->intno])
	{
		interrupt_handlers[ctx->intno](ctx);
	}
	else
	{
		// kprintf("No interrupt handler set for interrupt %d!\n", ctx->intno);
	}

	// If the interrupt came from PIC, we need to 
	// inform it that we are OK to get more
	if(ctx->intno >= 0x20 && ctx->intno <= 0x29)
	{
		pic_eoi(ctx->intno);
	}
	return;
}

// Should the entry actually just be a number (offset)?
void idt_set_gate(int idx, uint32_t handler, uint8_t type, uint8_t dpl)
{
  IDT_t* entry = &idt[idx];
  entry->offset_lo = handler & 0xFFFF;
  entry->selector = 0x8;
  entry->zero_byte = 0;
  entry->type_attr = (1 << 7) | (dpl << 5) | type;
  entry->offset_hi = (handler >> 16) & 0xFFFF;
  return;
}

void idt_init()
{
	pic_init();

	memset(interrupt_handlers, IDT_INTERRUPT_COUNT, sizeof(interrupt_handler));

	for(int i = 0; i < IDT_INTERRUPT_COUNT; i++)
	{
		idt_set_gate(i, interrupt_fpointers[i], IDT_GATE_TYPE_INTR, 0);
	}

	uint64_t idtr_operand = (uint64_t)((sizeof(idt) - 1) | ((uint64_t)(uint32_t)idt << 16));
	__asm__ __volatile__("lidt %0" : : "m" (idtr_operand));
	return;
}