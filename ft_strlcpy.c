#include "libft.h"

size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t src_len;
    size_t i;

    src_len = ft_strlen(src);
    i = 0;
    if (size == 0)
        return (src_len);
    while (src[i] != '\0' && i < size - 1)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return src_len;
}