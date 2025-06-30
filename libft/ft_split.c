/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:10:25 by hgenc             #+#    #+#             */
/*   Updated: 2025/06/30 10:10:27 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_words(const char *s, char c)
{
	int		count;
	int		in_word;
	size_t	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (in_word == 0)
			{
				in_word = 1;
				count++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

static size_t	get_word_len(const char *s, size_t start_index, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = start_index;
	while (s[i] != '\0' && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	**free_result(char **result, size_t count)
{
	while (count > 0)
	{
		count--;
		free(result[count]);
		result[count] = NULL;
	}
	free(result);
	return (NULL);
}

static char	*create_and_copy_word(const char *s,
		size_t start_index, char c)
{
	size_t	word_len;
	char	*word;

	word_len = get_word_len(s, start_index, c);
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (word == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(word, s + start_index, word_len + 1);
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	num_words;
	size_t	i;
	size_t	word_idx;

	if (s == NULL)
		return (NULL);
	num_words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	word_idx = -1;
	while (++word_idx < num_words)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		result[word_idx] = create_and_copy_word(s, i, c);
		if (result[word_idx] == NULL)
			return (free_result(result, word_idx));
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	result[word_idx] = NULL;
	return (result);
}
