/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:34:09 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/05 15:08:57 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	count_lines(char *text)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (text[i])
	{
		if (text[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && text[i - 1] != '\n')
		count++;
	return (count);
}

static void	split_text(char *text, char **lines)
{
	size_t	i;
	size_t	line_idx;

	i = 0;
	line_idx = 0;
	lines[line_idx] = &text[0];
	while (text[i])
	{
		if (text[i] == '\n')
		{
			text[i] = '\0';
			if (text[i + 1])
				lines[++line_idx] = &text[i + 1];
		}
		i++;
	}
}

char	**split_lines(char *text, size_t *line_count)
{
	size_t	count;
	char	**lines;

	if (!text)
		return (NULL);
	count = count_lines(text);
	if (count == 0)
		return (free(text), NULL);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (free(text), NULL);
	split_text(text, lines);
	lines[count] = NULL;
	*line_count = count;
	return (lines);
}
