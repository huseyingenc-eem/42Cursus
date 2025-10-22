/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:33:40 by hgenc             #+#    #+#             */
/*   Updated: 2025/08/07 14:33:41 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*buffer || !(*buffer)[0])
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
	{
		line = ft_substr(*buffer, 0, i + 1);
		temp = ft_substr(*buffer, i + 1, ft_strlen(*buffer) - (i + 1));
		free(*buffer);
		*buffer = temp;
		return (line);
	}
	line = *buffer;
	*buffer = NULL;
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
