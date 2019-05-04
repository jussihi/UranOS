#include <uranos/arch.h>
#include <uranos/console.h>
#include <uranos/kernel.h>		// kprintf
#include <stddef.h>

int kmain(void)
{
	/* Initialize architecture (arch/x86/init) */
	init_arch();
	console_init();
	kprintf("1\n");
	kprintf("2\n");
	kprintf("3\n");
	kprintf("4\n");
	kprintf("5\n");
	kprintf("6\n");
	kprintf("7\n");
	kprintf("8\n");
	kprintf("9\n");
	kprintf("10\n");
	kprintf("11\n");
	kprintf("Hello world from kernel! This should be pretty long message and exceed the 80 char treshold\n");
	kprintf("12\n");
	kprintf("13\n");
	kprintf("14\n");
	kprintf("15\n");
	kprintf("16\n");
	kprintf("17\n");
	kprintf("18\n");
	kprintf("19\n");
	kprintf("20\n");
	kprintf("21\n");
	kprintf("22\n");
	kprintf("23\n");
	kprintf("Another very long message to test the 80-char newline treshold... It seems to work fine ...\n");
	kprintf("Testing 0x%x for hex and %d for decimals and %s for strings.\n", 16, 10, "testi");
	while(1);
}