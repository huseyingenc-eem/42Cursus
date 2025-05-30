/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:36 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:35 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    char *ptr;
    size_t total_size;
    size_t i;
    size_t j;

    if (!s1 || !s2)
        return (NULL);
    total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
    ptr = malloc(total_size);
    if (!ptr)
        return (NULL);
    i = -1;
    while (s1[++i])
        ptr[i] = s1[i];
    j = -1;
    while(s2[++j])
        ptr[i + j] = s2[j];
    ptr[i + j] = '\0';
    return (ptr);
}
