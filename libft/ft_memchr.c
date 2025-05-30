/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:45:37 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:54 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    const unsigned char *s_ptr;
    size_t i;

    s_ptr = s;
    i = 0;
    while (i < n)
    {
        if (s_ptr[i] == (unsigned char)c)
            return ((void *)(s_ptr + i));
        i++;
    }
    return (NULL);
}
