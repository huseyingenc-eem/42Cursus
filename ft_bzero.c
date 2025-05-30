void ft_bzero(void *s, size_t n)
{
    size_t i;
    unsigned char *byte_ptr;

    byte_ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        byte_ptr[i] = '\0';
        i++;
    }
}