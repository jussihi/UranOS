#ifndef __URANOS_X86_TSS_H
#define __URANOS_X86_TSS_H

#include <stdint.h>

typedef struct __attribute((__packed__)) {
  uint16_t link, :16;
  void* esp0;
  uint16_t ss0, :16;
  void* esp1;
  uint16_t ss1, :16;
  void* esp2;
  uint16_t ss2, :16;
  uint32_t cr3;
  void (*eip)(void);
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint16_t es, :16;
  uint16_t cs, :16;
  uint16_t ss, :16;
  uint16_t ds, :16;
  uint16_t fs, :16;
  uint16_t gs, :16;
  uint16_t ldtr, :16;
  uint16_t reserved, iopb;
} TSS_t;


void tss_init(void);

TSS_t* get_tss(void);

#endif /* __URANOS_X86_GDT_H */