/*
 * This is the string.h header and functions defined for the UranOS.
 * Many of the functions are not word-oriented, so the performance is 
 * very poor.
 */


#ifndef _URANOS_STRING_HH
#define _URANOS_STRING_HH

#include "stddef.h"

#include <stdint.h>


// check faster 32-bit aligned from 
// https://sourceware.org/viewvc/src/newlib/libc/string/memchr.c?revision=1.4&view=markup
static inline void* memchr(const void* _s, int _c, size_t _n)
{
    const unsigned char* s = _s;
    unsigned char c = _c;
    while(_n--)
    {
        if(*s++ == c)
        {
            return (void*)s;
        }
    }
    return NULL;
}


// again byte oriented slow stuff ...
static inline int memcmp(const void* _s1, const void* _s2, size_t _n)
{
    const unsigned char *c1 = _s1, *c2 = _s2;
    while(_n-- && (*c1++ == *c2++));
    return *c1 - *c2;
}


// mem - functions
static inline void* memcpy(void* _dest, const void* _src, size_t _num)
{
    // byte oriented slooow copy (optimize for 32-bit later!)
    const char* src = _src;
    char* dest = _dest;
    while(_num--)
    {
        *dest++ = *src++;
    }
    return _dest;
}


// yuck, disgusting
static inline void* memmove(void* _dest, const void* _src, size_t _num)
{
    uint8_t* dest = _dest;
    if(_src > _dest)
    {
        while(_num--)
        {
            *dest++ = *(uint8_t*)_src++;
        }
    }
    else
    {
        dest += _num;
        _src += _num;
        while(_num--)
        {
            *--dest = *(uint8_t*)--_src;
        }
    }
    return _dest;
}


static inline void* memset(void* _s, int _c, size_t _n)
{
    unsigned char* s = _s;
    unsigned char c = _c;
    while(_n--)
    {
        *s++ = c;
    }
    return _s;
}


static inline char* strcat(char* _dest, const char* _src)
{
    char* save = _dest;
    while(*_dest)
    {
        _dest++;
    }
    while(*_dest++ = *_src++);
    return save;
}


static inline char* strchr(const char* _s, int _c)
{
    char c = _c;
    while(*_s++ != c);
    if(*_s == 0)
    {
        return NULL;
    }
    return (char *)_s;
}


static inline int strcmp(const char* _str1, const char* _str2)
{
    while(*_str1 && (*_str1++ == *_str2++));
    return *(const unsigned char*)_str1 - *(const unsigned char*)_str2;
}


static inline int strcoll(const char* _s1, const char* _s2)
{
    // TODO: implement this
    return 0;
}


static inline char* strcpy(char* _dest, const char* _src)
{
    char* save = _dest;
    while(*_dest++ = *_src++);
    return save;
}


static inline size_t strcspn(const char *_s, const char *_reject)
{
    size_t rv = 0;
    while(*_s)
    {
        if(strchr(_reject,*_s))
        {
            return rv;
        }
        else
        {
            _s++,rv++;
        }
    }
    return rv;
}


static inline char* strerror(int _errnum)
{
    // TODO: Implement !
    return "not implemented!\n";
}


static inline size_t strlen(const char* _str)
{
    const char* orig = _str;
    while(*(_str++));
    return (size_t)(_str - orig - 1);
}


static inline char* strncat(char* _dest, const char* _src, size_t _n)
{
    char* save = _dest;
    size_t i = 0;
    while(*_dest)
    {
        _dest++;
    }
    while(i++ != _n && (*_dest++ = *_src++));
    return save;
}


static inline int strncmp(const char* _str1, const char* _str2, size_t _n)
{
    size_t i = 0;
    while(i++ != _n && *_str1 && (*_str1++ == *_str2++));
    return *(const unsigned char*)_str1 - *(const unsigned char*)_str2;
}


static inline char* strncpy(char* _dest, const char* _src, size_t _n)
{
    char* save = _dest;
    size_t i = 0;
    while(i++ != _n && (*_dest++ = *_src++));
    return save;
}


static inline char* strpbrk(const char* _s1, const char* _s2)
{
    while(*_s1)
    {
        if(strchr(_s2, *_s1++))
        {
            return (char*)--_s1;
        }
    }
    return NULL;
}


static inline char* strrchr(const char* _s, int _c)
{
    char c = _c;
    char* last = NULL;
    while(*_s)
    {
        if(*_s == c)
        {
            last = (char*)_s;
        }
        _s++;
    }
    return last;
}

static inline size_t strspn(const char* _s, const char* _accept)
{
    size_t rv = 0;
    while(*_s && strchr(_accept,*_s++))
    {
        rv++;
    }
    return rv;
}


static inline char* strstr(const char* _s1, const char* _s2)
{
    size_t n = strlen(_s2);
    while(*_s1)
    {
        if(!memcmp(_s1++,_s2,n))
        {
            return (char*)_s1-1;
        }
    }
    return NULL;
}

// borrowed from the spooky internet, hope it works!
static inline char* strtok(char* _str, const char* _delim)
{
    static char* p=0;
    if(_str)
    {
        p=_str;
    }
    else if(!p)
    {
        return 0;
    }
    _str = p + strspn(p, _delim);
    p = _str + strcspn(_str, _delim);
    if(p == _str)
    {
        return p = 0;
    }
    p = *p ? *p=0,p+1 : 0;
    return _str;
}


static inline size_t strxfrm(char* _dest, const char* _src, size_t _n)
{
    // TODO: implement !
    return 0;
}


#endif 