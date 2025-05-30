#include "libft.h"

char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    size_t s_len;
    size_t i;
    char *ptr;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    ptr = malloc(s_len + 1);
    if (!ptr)
        return (NULL);
    i = -1;
    while (s[++i] != '\0')
        ptr[i] = f(i, s[i]);
    ptr[i] = '\0';
    return (ptr);
}