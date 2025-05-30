/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:59 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:21 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t i;
    size_t j;

    if (*needle == '\0')
        return ((char *)haystack);
    i = 0;
    while (i < len && haystack[i])
    {
        j = 0;
        while (i + j < len && haystack[i + j]
            && haystack[i + j] == needle[j])
            j++;
        if (needle[j] == '\0')
            return ((char *)(haystack + i));
        i++;
    }
    return (NULL);
}

