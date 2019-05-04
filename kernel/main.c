#include <uranos/arch.h>
#include <uranos/console.h>
#include <uranos/kernel.h>		// kprintf

int kmain(void)
{
	/* Initialize architecture (arch/x86/init) */
	init_arch();
	console_init();
	kprintf("Hello world from kernel!");
	while(1);
}