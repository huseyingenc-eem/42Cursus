void *ft_memchr(const void *s, int c, size_t n)
{
    const unsigned char *s_ptr;
    size_t i;

    s_ptr = s;
    i = 0;
    while (i < n)
    {
        if (s_ptr[i] == (unsigned char)c)
            return ((void *)(s_ptr + i));
        i++;
    }
    return (NULL);
}