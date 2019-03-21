#include <uranos/arch.h>

int kmain(void)
{
	/* Initialize architecture (arch/x86/init) */
	init_arch();
	while(1);
}