#include "push_swap.h"
#include <stdlib.h>

static int	count_words(const char *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (ps_is_space(*s))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*extract_word(const char **s)
{
	const char	*start;
	int			len;
	char		*word;
	int			i;

	while (ps_is_space(**s))
		(*s)++;
	start = *s;
	len = 0;
	while ((*s)[len] && !ps_is_space((*s)[len]))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	*s += len;
	return (word);
}

char	**ps_split_ws(const char *s)
{
	char	**arr;
	int		wc;
	int		i;

	if (!s)
		return (NULL);
	wc = count_words(s);
	arr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		arr[i] = extract_word(&s);
		if (!arr[i])
		{
			ps_free_split(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	ps_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	has_duplicate(int *vals, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (vals[i] == vals[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	parse_single_arg(t_ps *ps, char *arg)
{
	char	**tokens;
	int		*vals;
	int		count;
	int		i;

	tokens = ps_split_ws(arg);
	if (!tokens || !tokens[0])
	{
		ps_free_split(tokens);
		return (0);
	}
	count = 0;
	while (tokens[count])
		count++;
	vals = (int *)malloc(sizeof(int) * count);
	if (!vals)
	{
		ps_free_split(tokens);
		return (0);
	}
	i = 0;
	while (i < count)
	{
		if (!ps_atoi_safe(tokens[i], &vals[i]))
		{
			free(vals);
			ps_free_split(tokens);
			return (0);
		}
		i++;
	}
	ps_free_split(tokens);
	if (has_duplicate(vals, count))
	{
		free(vals);
		return (0);
	}
	i = 0;
	while (i < count)
	{
		ps_push_back(&ps->a, ps_new_node(vals[i]));
		i++;
	}
	ps->size_a = count;
	free(vals);
	return (1);
}

static int	parse_multi_args(t_ps *ps, int argc, char **argv)
{
	int	*vals;
	int	i;

	vals = (int *)malloc(sizeof(int) * (argc - 1));
	if (!vals)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!ps_atoi_safe(argv[i], &vals[i - 1]))
		{
			free(vals);
			return (0);
		}
		i++;
	}
	if (has_duplicate(vals, argc - 1))
	{
		free(vals);
		return (0);
	}
	i = 0;
	while (i < argc - 1)
	{
		ps_push_back(&ps->a, ps_new_node(vals[i]));
		i++;
	}
	ps->size_a = argc - 1;
	free(vals);
	return (1);
}

int	parse_args(t_ps *ps, int argc, char **argv)
{
	if (argc == 2)
		return (parse_single_arg(ps, argv[1]));
	else
		return (parse_multi_args(ps, argc, argv));
}
