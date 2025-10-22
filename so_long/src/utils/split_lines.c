#include "../../include/utils.h"
#include <stdlib.h>

char	**split_lines(char *text, size_t *line_count)
{
    size_t	count;
    size_t	index;
    char	**lines;
    size_t	line_index;

    if (!text)
        return (NULL);
    count = 0;
    index = 0;
    while (text[index])
    {
        if (text[index] == '\n')
            count++;
        index++;
    }
    if (index > 0 && text[index - 1] != '\n')
        count++;
    lines = malloc(sizeof(char *) * (count + 1));
    if (!lines)
        return (NULL);
    index = 0;
    line_index = 0;
    lines[line_index] = &text[0];
    while (text[index])
    {
        if (text[index] == '\n')
        {
            text[index] = '\0';
            if (text[index + 1])
                lines[++line_index] = &text[index + 1];
        }
        index++;
    }
    lines[count] = NULL;
    *line_count = count;
    return (lines);
}