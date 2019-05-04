#include <uranos/arch.h>

#include <stdint.h>

void init_arch(void)
{
	gdt_init();
	/* Set VGA memory to test if the system works. */
	*(uint16_t *)(0xC03FF000) = 0x0141;
}