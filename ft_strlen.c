size_t ft_strlen(const char *c)
{
    size_t count;

    count = 0;
    while (c[count] != '\0')
        count++;
    return (count);
}