#include <uranos/bitmap.h>



int bm_destroy(bitmap_t* bm)
{
	return 0;
}

size_t bm_sizeof(bitmap_t* bm)
{
	return bm->bit_count;
}

void bm_set_bit_value(bitmap_t* bm, size_t idx, uint8_t value)
{
	return;
}

void bm_set_bit_off(bitmap_t* bm, size_t idx)
{
	return;
}

void bm_set_bit_on(bitmap_t* bm, size_t idx)
{
	return;
}

void bm_set_bit_flip(bitmap_t* bm, size_t idx)
{
	return;
}

uint8_t bm_test_bit(bitmap_t* bm, size_t idx)
{
	return 0;
}

void bm_set_all(bitmap_t* bm, uint8_t value)
{

	return;
}