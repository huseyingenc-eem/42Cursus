#include "../../include/utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

char	*read_file(const char *path)
{
    int		file_descriptor;
    char	buffer[BUFFER_SIZE];
    char	*result;
    ssize_t	bytes_read;
    size_t	total_size;

    file_descriptor = open(path, O_RDONLY);
    if (file_descriptor < 0)
        return (NULL);
    result = NULL;
    total_size = 0;
    while ((bytes_read = read(file_descriptor, buffer, BUFFER_SIZE)) > 0)
    {
        char	*temp;
        size_t	i;

        temp = malloc(total_size + bytes_read + 1);
        if (!temp)
        {
            free(result);
            close(file_descriptor);
            return (NULL);
        }
        i = 0;
        while (i < total_size && result)
        {
            temp[i] = result[i];
            i++;
        }
        free(result);
        i = 0;
        while (i < (size_t)bytes_read)
        {
            temp[total_size + i] = buffer[i];
            i++;
        }
        total_size += bytes_read;
        temp[total_size] = '\0';
        result = temp;
    }
    close(file_descriptor);
    return (result);
}