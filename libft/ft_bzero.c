/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:43:03 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:46:11 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_bzero(void *s, size_t n)
{
    size_t i;
    unsigned char *byte_ptr;

    byte_ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        byte_ptr[i] = '\0';
        i++;
    }
}