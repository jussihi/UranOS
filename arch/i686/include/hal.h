#ifndef __URANOS_X86_HAL_HH
#define __URANOS_X86_HAL_HH

#include <stdint.h>

uint8_t inb(uint16_t w_port);

void outb(uint16_t w_port, uint8_t w_byte);

uint16_t inw(uint16_t w_port);

void outw(uint16_t w_port, uint16_t w_short);

uint32_t inl(uint16_t w_port);

void outl(uint16_t w_port, uint32_t w_long);

#endif