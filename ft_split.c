#include "libft.h"

int ft_count_words(char const *s, char c)
{
    size_t count;
    size_t i;
    int in_word;

    count = 0;
    i = 0;
    in_word = 0;
    while (s[i])
    {
        if (s[i] != c && in_word == 0)
        {
            in_word = 1;
            count++;
        }
        else if (s[i] == c)
            in_word = 0;
        i++;
    }
    return (count);
}

char **ft_split(char const *s, char c)
{
    char **str_arr;
    char *str;
    size_t arr_size;
    size_t i;

    if (!s)
        return (NULL);
    arr_size = ft_count_words(s, c);
    str_arr = (char **)malloc(arr_size + 1);
    if (!str_arr)
        return (NULL);
    while (*s)
    {
        if (*s == c)
            s++;
        else
        {
            int word_len = ft_strchr(s, c) - s;
        }
    }
}