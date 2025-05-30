void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *dest_ptr;
    const unsigned char *src_ptr;
    size_t i;

    dest_ptr = dest;
    src_ptr = src;
    i = 0;
    while (i < n)
    {
        dest_ptr[i] = src_ptr[i];
        i++;
    }
    return (dest);
}