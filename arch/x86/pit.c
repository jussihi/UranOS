#include <pit.h>
#include <idt.h>
#include <uranos/kernel.h>

// once we get tasking working, we create a 
// real interrupt handler with tasking
static void pit_irq_dummy(pt_regs* ctx)
{
	kprintf("got a pit interrupt\n");
	return;
}

void pit_init()
{
	interrupt_register_handler(pit_irq_dummy, 32, 0, 0);
}