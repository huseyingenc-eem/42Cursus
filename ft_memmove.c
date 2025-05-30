void *ft_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *dest_ptr;
    const unsigned char *src_ptr;
    size_t i;

    dest_ptr = dest;
    src_ptr = src;
    i = 0;
    if (dest_ptr < src_ptr)
    {
        while (i < n)
        {
            dest_ptr[i] = src_ptr[i];
            i++;
        }
    } else
    {
        while (n > 0)
        {
            dest_ptr[n - 1] = src_ptr[n - 1];
            n--;
        }
    }
    return (dest);
}