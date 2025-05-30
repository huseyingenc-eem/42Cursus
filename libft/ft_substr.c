/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:49:42 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:49:43 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *ptr;

    if (!s)
        return (NULL);
    if (start >= ft_strlen(s))
    {
        ptr = malloc(1);
        if (ptr == NULL)
            return (NULL);
        ptr[0] = '\0';
        return (ptr);
    }
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start;
    ptr = malloc(len + 1);
    if (ptr == NULL)
        return (NULL);
    ft_strlcpy(ptr, s + start, len + 1);
    return (ptr);
}