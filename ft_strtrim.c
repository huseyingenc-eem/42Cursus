#include "libft.h"

char *ft_strtrim(char const *s1, char const *set)
{
    char *ptr;
    size_t str_len;

    if (!s1 || !set)
        return (NULL);
    while (s1 && ft_strchr(set, *s1) != NULL)
        s1++;
    str_len = ft_strlen(s1);
    while (str_len > 0 && ft_strchr(set, s1[str_len - 1]) != NULL)
        str_len--;
    ptr = malloc(str_len + 1);
    if (!ptr)
        return (NULL);
    ft_memcpy(ptr, s1, str_len);
    ptr[str_len] = '\0';
    return (ptr);
}