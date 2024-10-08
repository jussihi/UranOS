#include <uranos/bitmap.h>
#include <uranos/kernel.h>


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
    bm->bits[idx/BITS_PER_LONG] |= (!!value << (BITS_PER_LONG-idx-1));
    return;
}

void bm_set_bit_off(bitmap_t* bm, size_t idx)
{
    bm->bits[idx/BITS_PER_LONG] &= ~(1 << (BITS_PER_LONG-idx-1));
    return;
}

void bm_set_bit_on(bitmap_t* bm, size_t idx)
{
    bm->bits[idx/BITS_PER_LONG] |= (1 << (BITS_PER_LONG-idx-1));
    return;
}

void bm_set_bit_flip(bitmap_t* bm, size_t idx)
{
    bm->bits[idx/BITS_PER_LONG] ^= (1 << (BITS_PER_LONG-idx-1));
    return;
}

uint8_t bm_test_bit(bitmap_t* bm, size_t idx)
{
    return ((bm->bits[idx/BITS_PER_LONG] >> (BITS_PER_LONG-idx-1)) & 1);
}

void bm_set_all(bitmap_t* bm, uint8_t value)
{
  int chunks = bm_sizeof(bm) / BITS_PER_LONG;
  for(int i = 0; i < chunks; i++)
  {
    if(value)
    {
      bm->bits[i] = LONG_MAX_VALUE;
    }
    else
    {
      bm->bits[i] = 0;
    }
  }

  int remainder = bm_sizeof(bm) % BITS_PER_LONG;
  if(remainder)
  {
    for(int i = 0; i < remainder; i++)
    {
      bm_set_bit_value(bm, chunks * BITS_PER_LONG + i, value);
    }
  }

    return;
}

int32_t bm_scan(bitmap_t* bm, uint8_t value, uint32_t count)
{
  if(count <= bm->bit_count)
  {
    for(uint32_t i = 0; i < bm->bit_count - count; i++)
    {
      uint32_t j;
      for(j = i; j < i + count; j++)
      {
        if(bm_test_bit(bm, j) != value)
        {
          break;
        }
      }
      if(j == i + count)
      {
        return i;
      }
    }
    return -1;
  }
  return -1;
}