#ifndef __URANOS_ITOA_HH
#define __URANOS_ITOA_HH

#include <uranos/arch.h>

char* __int_str(intmax_t i, char b[], int base, int plus_sign_if_needed, int space_sign_if_needed,
                int padding_no, int justify, int zero_pad);


#endif