/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:33 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:37 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *s1)
{
    size_t str_len;
    size_t i;
    char *ptr;

    str_len = ft_strlen(s1);
    i = -1;
    ptr = malloc(str_len + 1);
    if (ptr == NULL)
        return (NULL);
    while (++i < str_len)
        ptr[i] = s1[i];
    ptr[i] = '\0';
    return (ptr);
}
