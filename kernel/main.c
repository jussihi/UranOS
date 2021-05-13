#include <uranos/arch.h>
#include <uranos/console.h>
#include <uranos/kernel.h>		// kprintf
#include <uranos/pfalloc.h>
#include <uranos/heap.h>
#include <stddef.h>

int kmain(void)
{
	/* Initialize architecture (arch/x86/init) */
	console_init();
	init_arch();
	pfalloc_init();
	kprintf("Testing 0x%x for hex and %d for decimals and %s for strings.\n", 16, 10, "testi");
	kprintf("Enabling interrupts ...\n");
	//__asm__ __volatile__ ("sti");

	uintptr_t respages = pfalloc_pages(3);
	kprintf("Successfully allocated 3 pages from address %x!\n", respages);

	respages = pfalloc_pages(256);
	kprintf("Successfully allocated 256 pages from address %x!\n", respages);
	respages = pfalloc_pages(256);
	kprintf("Successfully allocated 256 pages from address %x!\n", respages);
	kprintf("Location of kprintf is 0x%x\n", &kprintf);
	while(1);
}