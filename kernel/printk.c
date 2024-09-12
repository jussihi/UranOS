#include <uranos/kernel.h>
#include <uranos/console.h>
#include <uranos/string.h> /* strlen */
#include <uranos/stdlib.h> /* itoa */
#include <uranos/type.h>   /* isdigit */
#include <uranos/itoa.h>

#include <stdarg.h>

extern console_t *console;

void __display_char(char c, int *a)
{
    console_putc(c);
    *a += 1;
}

void __display_str(char *c, int *a)
{
    for (int i = 0; c[i]; ++i)
    {
        __display_char(c[i], a);
    }
}

int vprintf(const char *fmt, va_list list)
{
    int chars = 0;
    char int_str_buffer[256];
    memset(int_str_buffer, 0, 256);
    for (int i = 0; fmt[i]; ++i)
    {
        char specifier = '\0';
        char length = '\0';

        int length_spec = 0;
        int prec_spec = 0;
        int left_justify = 0;
        int zero_pad = 0;
        int space_no_sign = 0;
        int alt_form = 0;
        int plus_sign = 0;
        int emode = 0;
        int expo = 0;

        if (fmt[i] == '%')
        {
            ++i;
            int extBreak = 0;
            while (1)
            {

                switch (fmt[i])
                {
                case '-':
                    left_justify = 1;
                    ++i;
                    break;

                case '+':
                    plus_sign = 1;
                    ++i;
                    break;

                case '#':
                    alt_form = 1;
                    ++i;
                    break;

                case ' ':
                    space_no_sign = 1;
                    ++i;
                    break;

                case '0':
                    zero_pad = 1;
                    ++i;
                    break;

                default:
                    extBreak = 1;
                    break;
                }

                if (extBreak)
                    break;
            }

            while (isdigit(fmt[i]))
            {
                length_spec *= 10;
                length_spec += fmt[i] - 48;
                ++i;
            }

            if (fmt[i] == '*')
            {
                length_spec = va_arg(list, int);
                ++i;
            }

            if (fmt[i] == '.')
            {
                ++i;
                while (isdigit(fmt[i]))
                {
                    prec_spec *= 10;
                    prec_spec += fmt[i] - 48;
                    ++i;
                }

                if (fmt[i] == '*')
                {
                    prec_spec = va_arg(list, int);
                    ++i;
                }
            }
            else
            {
                prec_spec = 6;
            }

            if (fmt[i] == 'h' || fmt[i] == 'l' || fmt[i] == 'j' ||
                fmt[i] == 'z' || fmt[i] == 't' || fmt[i] == 'L')
            {
                length = fmt[i];
                ++i;
                if (fmt[i] == 'h')
                {
                    length = 'H';
                }
                else if (fmt[i] == 'l')
                {
                    length = 'q';
                    ++i;
                }
            }
            specifier = fmt[i];
            memset(int_str_buffer, 0, 256);

            int base = 10;
            if (specifier == 'o')
            {
                base = 8;
                specifier = 'u';
                if (alt_form)
                {
                    __display_str("0", &chars);
                }
            }
            if (specifier == 'p')
            {
                base = 16;
                length = 'z';
                specifier = 'u';
            }
            switch (specifier)
            {
            case 'X':
                base = 16;
            case 'x':
                base = base == 10 ? 17 : base;
                if (alt_form)
                {
                    __display_str("0x", &chars);
                }

            case 'u':
            {
                switch (length)
                {
                case 0:
                {
                    unsigned int integer = va_arg(list, unsigned int);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'H':
                {
                    unsigned char integer = (unsigned char)va_arg(list, unsigned int);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'h':
                {
                    unsigned short int integer = va_arg(list, unsigned int);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'l':
                {
                    unsigned long integer = va_arg(list, unsigned long);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'j':
                {
                    uintmax_t integer = va_arg(list, uintmax_t);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'z':
                {
                    size_t integer = va_arg(list, size_t);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 't':
                {
                    ptrdiff_t integer = va_arg(list, ptrdiff_t);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                default:
                    break;
                }
                break;
            }

            case 'd':
            case 'i':
            {
                switch (length)
                {
                case 0:
                {
                    int integer = va_arg(list, int);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'H':
                {
                    signed char integer = (signed char)va_arg(list, int);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'h':
                {
                    short int integer = va_arg(list, int);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'l':
                {
                    long integer = va_arg(list, long);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'j':
                {
                    intmax_t integer = va_arg(list, intmax_t);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 'z':
                {
                    size_t integer = va_arg(list, size_t);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                case 't':
                {
                    ptrdiff_t integer = va_arg(list, ptrdiff_t);
                    __int_str(integer, int_str_buffer, base, plus_sign, space_no_sign, length_spec, left_justify, zero_pad);
                    __display_str(int_str_buffer, &chars);
                    break;
                }
                default:
                    break;
                }
                break;
            }

            case 'c':
            {
                __display_char(va_arg(list, int), &chars);
                break;
            }

            case 's':
            {
                __display_str(va_arg(list, char *), &chars);
                break;
            }

            case 'n':
            {
                switch (length)
                {
                case 'H':
                    *(va_arg(list, signed char *)) = chars;
                    break;
                case 'h':
                    *(va_arg(list, short int *)) = chars;
                    break;

                case 0:
                {
                    int *a = va_arg(list, int *);
                    *a = chars;
                    break;
                }

                case 'l':
                    *(va_arg(list, long *)) = chars;
                    break;
                case 'j':
                    *(va_arg(list, intmax_t *)) = chars;
                    break;
                case 'z':
                    *(va_arg(list, size_t *)) = chars;
                    break;
                case 't':
                    *(va_arg(list, ptrdiff_t *)) = chars;
                    break;
                default:
                    break;
                }
                break;
            }

            case 'e':
            case 'E':
                emode = 1;

            case 'f':
            case 'F':
            case 'g':
            case 'G':
            {
                double floating = va_arg(list, double);

                while (emode && floating >= 10)
                {
                    floating /= 10;
                    ++expo;
                }

                int form = length_spec - prec_spec - expo - (prec_spec || alt_form ? 1 : 0);
                if (emode)
                {
                    form -= 4; // 'e+00'
                }
                if (form < 0)
                {
                    form = 0;
                }

                __int_str(floating, int_str_buffer, base, plus_sign, space_no_sign, form,
                          left_justify, zero_pad);

                __display_str(int_str_buffer, &chars);

                floating -= (int)floating;

                for (int i = 0; i < prec_spec; ++i)
                {
                    floating *= 10;
                }
                intmax_t decPlaces = (intmax_t)(floating + 0.5);

                if (prec_spec)
                {
                    __display_char('.', &chars);
                    __int_str(decPlaces, int_str_buffer, 10, 0, 0, 0, 0, 0);
                    int_str_buffer[prec_spec] = 0;
                    __display_str(int_str_buffer, &chars);
                }
                else if (alt_form)
                {
                    __display_char('.', &chars);
                }

                break;
            }

            default:
                break;
            }

            if (specifier == 'e')
            {
                __display_str("e+", &chars);
            }
            else if (specifier == 'E')
            {
                __display_str("E+", &chars);
            }

            if (specifier == 'e' || specifier == 'E')
            {
                __int_str(expo, int_str_buffer, 10, 0, 0, 2, 0, 1);
                __display_str(int_str_buffer, &chars);
            }
        }
        else
        {
            __display_char(fmt[i], &chars);
        }
    }

    return chars;
}

int kprintf(const char *fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    int i = vprintf(fmt, list);
    va_end(list);
    return i;
}