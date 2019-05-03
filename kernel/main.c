#include <uranos/arch.h>
#include <uranos/console.h>

int kmain(void)
{
	/* Initialize architecture (arch/x86/init) */
	init_arch();
	console_init();
	while(1);
}