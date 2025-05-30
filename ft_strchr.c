char *strchr(const char *s, int c)
{
    while (1)
    {
        if (*s == (char)c)
            return ((char *)s);
        if (*s == '\0')
            return (NULL);
        s++;
    }
}