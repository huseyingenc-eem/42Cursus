/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:10:37 by hgenc             #+#    #+#             */
/*   Updated: 2025/06/30 10:10:38 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	str_len;
	size_t	i;
	char	*ptr;

	str_len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (str_len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
