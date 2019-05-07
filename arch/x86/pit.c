#include <pit.h>
#include <idt.h>

// once we get tasking working, we create a 
// real interrupt handler with tasking
static void pit_irq_dummy(pt_regs* ctx)
{
	return;
}

void pit_init()
{
	interrupt_register_handler(pit_irq_dummy, 32, 0, 0);
}