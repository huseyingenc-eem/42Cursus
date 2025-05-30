#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
    char *candidate;
    size_t s_len;
    size_t i;

    s_len = ft_strlen(s);
    i = 0;
    candidate = NULL;
    while (i <= s_len)
    {
        if (s[i] == (char)c)
            candidate = (char *)s + i;
        i++;
    }
    return (candidate);
}