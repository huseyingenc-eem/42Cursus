int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *s1_ptr;
    const unsigned char *s2_ptr;
    size_t i;

    s1_ptr = s1;
    s2_ptr = s2;
    i = 0;
    while (i < n)
    {
        if (s1_ptr[i] != s2_ptr[i])
            return (s1_ptr[i] - s2_ptr[i]);
        i++;
    }
    return (NULL);
}