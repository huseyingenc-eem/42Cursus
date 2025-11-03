/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:07:40 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/03 16:01:11 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*join_buffers(char *old, char *new_buf, size_t old_size,
		size_t new_size)
{
	char	*result;
	size_t	i;

	result = malloc(old_size + new_size + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < old_size && old)
		result[i] = old[i];
	i = -1;
	while (++i < new_size)
		result[old_size + i] = new_buf[i];
	result[old_size + new_size] = '\0';
	return (result);
}

static char	*read_loop(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*result;
	char	*temp;
	ssize_t	bytes_read;
	size_t	total_size;

	result = NULL;
	total_size = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp = join_buffers(result, buffer, total_size, bytes_read);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		free(result);
		result = temp;
		total_size += bytes_read;
	}
	return (result);
}

char	*read_file(const char *path)
{
	int		fd;
	char	*result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = read_loop(fd);
	close(fd);
	return (result);
}
