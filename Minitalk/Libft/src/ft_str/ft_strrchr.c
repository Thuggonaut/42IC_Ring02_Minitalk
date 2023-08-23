#include "libft.h"

char* ft_strrchr(const char* str, int c) 
{
    int p;
    
    p = ft_strlen(str);
    while (p >= 0)
    {
        if (str[p] == (unsigned char)c) 
            return (char*)str + p;
        p--;
    }
    return (NULL);
}
