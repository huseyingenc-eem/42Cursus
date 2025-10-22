#include "../../include/utils.h"

size_t	ft_strlen(const char *str)
{
    size_t	length;

    length = 0;
    if (!str)
        return (0);
    while (str[length])
        length++;
    return (length);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
    size_t	index;

    index = 0;
    while (index < n && str1[index] && str2[index])
    {
        if (str1[index] != str2[index])
            return ((unsigned char)str1[index] - (unsigned char)str2[index]);
        index++;
    }
    if (index < n)
        return ((unsigned char)str1[index] - (unsigned char)str2[index]);
    return (0);
}
