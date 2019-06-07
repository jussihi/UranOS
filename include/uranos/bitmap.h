#ifndef __URANOS_BITMAP_HH
#define __URANOS_BITMAP_HH

#include <uranos/arch.h>
#include <stddef.h>

typedef struct {
  size_t bit_count;
  bm_element* bits;
} bitmap_t;


// we actually need malloc for this
// bitmap_t* bm_create(size_t bit_count);

int bm_destroy(bitmap_t* bm);

size_t bm_sizeof(bitmap_t* bm);



void bm_set_bit_value(bitmap_t* bm, size_t idx, uint8_t value);
void bm_set_bit_off(bitmap_t* bm, size_t idx);
void bm_set_bit_on(bitmap_t* bm, size_t idx);
void bm_set_bit_flip(bitmap_t* bm, size_t idx);
uint8_t bm_test_bit(bitmap_t* bm, size_t idx);


void bm_set_all(bitmap_t* bm, uint8_t value);

int32_t bm_scan(bitmap_t* bm, uint8_t value, uint32_t count);


#endif /* __URANOS_BITMAP_HH */