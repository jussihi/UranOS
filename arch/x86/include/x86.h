#ifndef __URANOS_X86_CPU_H
#define __URANOS_X86_CPU_H

#define MAX_PAGE_FRAMES 32768 // 4 GiB
#define PAGE_SIZE 4096

#define BITS_PER_LONG 32
#define LONG_MAX_VALUE 4294967295

#define ENABLE_INTERRUPTS()  __asm__ __volatile__("sti")
#define DISABLE_INTERRUPTS() __asm__ __volatile__("cli")

#include <stdint.h>

typedef struct __attribute__((__packed__)) {
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t esp_bu;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
  uint16_t gs, :16;
  uint16_t fs, :16;
  uint16_t es, :16;
  uint16_t ds, :16;
  uint32_t intno;
  uint32_t errorno;
  void *framep;
  void (*eip) (void);
  uint16_t cs, :16;
  uint32_t eflags;
  void *esp;
  uint16_t ss, :16;
} pt_regs;

#endif /* __URANOS_X86_CPU_H */