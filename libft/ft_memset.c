/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:14 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:45 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memset(void *s, int c, size_t n)
{
    size_t i;
    unsigned char *byte_ptr;

    byte_ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        byte_ptr[i] = (unsigned char)c;
        i++;
    }
    return s;
}
