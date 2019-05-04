#include <stdint.h>

#include <gdt.h>
#include <tss.h>
#include <uranos/kernel.h>



typedef enum {
    GDT_GRAN_BYTE = 0,              /* Limit has 1-byte granularity. */
    GDT_GRAN_PAGE = 1               /* Limit has 4 kB granularity. */
} seg_granularity;

static GDT_t gdt[6];                /* The GDT structure containing 6 entries */

static void insert_segment_descriptor(GDT_t* entry, uint32_t base, uint32_t limit,
                                      int type, seg_granularity granularity)
{
  /* NULL everything! */
  *((uint64_t*)entry) = 0;

  /* put limit into right place */
  entry->limit_lo = limit & 0xFFFF;
  entry->flags_limit_nibbles |= (limit >> 16) & 0xF;

  /* Put base to right place */
  entry->base_lo  = base & 0xFFFF;
  entry->base_mid = (base >> 16) & 0xFF;
  entry->base_hi  = (base >> 24) & 0xFF;

  /* Type aka. access byte */
  entry->type = type;

  /* Flags (bits 52-55) */
  entry->flags_limit_nibbles |= granularity << 7; /* Granularity bit for paging */
  entry->flags_limit_nibbles |= 1 << 6;           /* Protected mode bit */

  // kprintf("base lo: %x, mi: %x hi: %x\n", entry->base_lo, entry->base_mid, entry->base_hi);

  return;
}


static uint64_t make_gdtr_descriptor(uint16_t limit, void* base)
{
  return limit | ((uint64_t) (uint32_t) base << 16);
}

void gdt_init()
{
  /* null descriptor, same as nulling first 8 bytes */
  ((uint64_t*)gdt)[0] = 0;  

  // see https://wiki.osdev.org/GDT Access byte image for more info especially regarding the type byte !

  /* Kernel code descriptor */
  insert_segment_descriptor(&gdt[1], 0, 0xfffff, 0x9A, GDT_GRAN_PAGE);  // 0x08

  /* Kernel data descriptor */
  insert_segment_descriptor(&gdt[2], 0, 0xfffff, 0x92, GDT_GRAN_PAGE);  // 0x10

  /* Userland ring3 code descriptor */
  insert_segment_descriptor(&gdt[3], 0, 0xfffff, 0xFA, GDT_GRAN_PAGE);  // 0x18

  /* Userland ring3 data descriptor */
  insert_segment_descriptor(&gdt[4], 0, 0xfffff, 0xF2, GDT_GRAN_PAGE);  // 0x20

  /* TODO: TSS descriptor */
  insert_segment_descriptor(&gdt[5], (uint32_t)get_tss(), sizeof(TSS_t), 0x89, GDT_GRAN_BYTE);  // 0x28

  // kprintf("TSS struct loaded to %d!\n", sizeof(TSS_t));

  /* Refresh the GDT pointer */
  uint64_t gdtr_descriptor = make_gdtr_descriptor(sizeof(gdt) - 1, gdt);
  __asm__ __volatile__ ("lgdt %0" : : "m" (gdtr_descriptor));
  /* Loads the TSS with its segment's offset */
  // __asm__ __volatile__ ("ltr %w0" : : "q" (0x28));
  return;
}
