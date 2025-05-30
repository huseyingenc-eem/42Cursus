/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:07 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:48:48 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *dest_ptr;
    const unsigned char *src_ptr;
    size_t i;

    dest_ptr = dest;
    src_ptr = src;
    i = 0;
    if (dest_ptr < src_ptr)
    {
        while (i < n)
        {
            dest_ptr[i] = src_ptr[i];
            i++;
        }
    } else
    {
        while (n > 0)
        {
            dest_ptr[n - 1] = src_ptr[n - 1];
            n--;
        }
    }
    return (dest);
}
