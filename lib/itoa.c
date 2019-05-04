#include <stddef.h>
#include <stdint.h>

// From internet, GPLv3
char* itoa(int32_t _v, char* _r, int32_t _b)
{
  // check validity
  if(_b < 2 || _b > 36)
  {
    *_r = 0;
    return _r; 
  }

  char* ptr  = _r;
  char* ptr1 = _r;
  char tmp_char;
  int32_t tmp_value;

  do {
    tmp_value = _v;
    _v /= _b;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - _v * _b)];
  } while(_v);

  // is the value neg?
  if(tmp_value < 0)
  {
    *ptr++ = '-';
  }
  *ptr-- = '\0';
  while(ptr1 < ptr)
  {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return _r;
}