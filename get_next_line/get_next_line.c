#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*next_line_start;
	int		line_len;
    char	*temp;

	if (!*buffer || !**buffer)
		return (NULL);
	next_line_start = ft_strchr(*buffer, '\n');
	if (next_line_start)
	{
		line_len = next_line_start - *buffer + 1;
		line = ft_substr(*buffer, 0, line_len);
		temp = ft_substr(*buffer, line_len, ft_strlen(*buffer) - line_len);
		free(*buffer);
		*buffer = temp;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strlen(*buffer));
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

static char	*read_and_process(int fd, char **buffer)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*buffer, '\n'))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buffer);
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, read_buffer);
	}
	free(read_buffer);
	return (extract_line(buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_and_process(fd, &buffer));
}
