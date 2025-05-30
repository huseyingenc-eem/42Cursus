/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:48:12 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:19 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
    char *candidate;
    size_t s_len;
    size_t i;

    s_len = ft_strlen(s);
    i = 0;
    candidate = NULL;
    while (i <= s_len)
    {
        if (s[i] == (char)c)
            candidate = (char *)s + i;
        i++;
    }
    return (candidate);
}
