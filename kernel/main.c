#include <uranos/arch.h>
#include <uranos/console.h>
#include <uranos/kernel.h>		// kprintf
#include <stddef.h>

int kmain(void)
{
	/* Initialize architecture (arch/x86/init) */
	console_init();
	init_arch();
	kprintf("Testing 0x%x for hex and %d for decimals and %s for strings.\n", 16, 10, "testi");
	kprintf("Enabling interrupts ...\n");
	__asm__ __volatile__ ("sti");
	while(1);
}