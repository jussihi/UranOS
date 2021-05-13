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


char *utoa(uint32_t _v, char *_r, int32_t _b)
{
  char temp[17];  //an int can only be 16 bits long
                  //at radix 2 (binary) the string
                  //is at most 16 + 1 null long.
  int32_t temp_loc = 0;
  int32_t digit;
  int32_t str_loc = 0;

  //construct a backward string of the number.
  do
  {
    digit = (uint32_t)_v % _b;
    if (digit < 10)
    {
      temp[temp_loc++] = digit + '0';
    }
    else
    {
      temp[temp_loc++] = digit - 10 + 'A';
    }
    _v /= _b;
  } while ((uint32_t)_v > 0);

  temp_loc--;


  //now reverse the string.
  while ( temp_loc >=0 ) {// while there are still chars
      _r[str_loc++] = temp[temp_loc--];    
  }
  _r[str_loc] = 0; // add null termination.

  return _r;
}