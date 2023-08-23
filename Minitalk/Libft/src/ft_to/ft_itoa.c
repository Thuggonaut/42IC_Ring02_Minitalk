#include "libft.h"

char *convert(int value, char *ptr, int base)
{
    int tmp_value;

    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    while (value) 
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    }
    return (ptr);
}

char *ft_itoa(int value, char *s, int base) 
{
    char *ptr;
    char *ptr1;
    char tmp_char;

    ptr = s;
    ptr1 = s;
    if (base < 2 || base > 36) 
    { 
        s[0] = '\0'; 
        return (s);
    }
    ptr = convert(value, ptr, base);
    if (value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) 
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return (s);
}