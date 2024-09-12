#include <hal.h>

uint8_t inb(uint16_t w_port)
{
	uint8_t ret;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (w_port));
	return ret;
}

void outb(uint16_t w_port, uint8_t w_byte)
{
	__asm__ __volatile__ ("outb %1, %0" :: "dN" (w_port), "a" (w_byte));
}

uint16_t inw(uint16_t w_port)
{
  uint16_t ret;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (w_port));
  return ret;
}

void outw(uint16_t w_port, uint16_t w_short)
{
  __asm__ __volatile__ ("outw %1, %0" :: "dN" (w_port), "a" (w_short));
}

uint32_t inl(uint16_t w_port)
{
  uint32_t ret;
  __asm__ __volatile__ ("inl %1, %0" : "=a" (ret) : "dN" (w_port));
  return ret;
}

void outl(uint16_t w_port, uint32_t w_long)
{
  __asm__ __volatile__ ("outl %1, %0" :: "dN" (w_port), "a" (w_long));
}