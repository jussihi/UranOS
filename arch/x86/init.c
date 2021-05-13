#include <uranos/arch.h>

#include <stdint.h>

void init_arch(void)
{
	tss_init();
	gdt_init();
	idt_init();
	pit_init();
	
}