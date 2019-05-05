#ifndef __URANOS_X86_GDT_H
#define __URANOS_X86_GDT_H

#include <stdint.h>

typedef struct __attribute__((__packed__)) {
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t base_mid;
  uint8_t type;
  uint8_t flags_limit_nibbles;
  uint8_t base_hi;
} GDT_t;


void gdt_init();

#endif /* __URANOS_X86_GDT_H */