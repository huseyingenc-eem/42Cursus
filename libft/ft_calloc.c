/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:45:11 by hgenc             #+#    #+#             */
/*   Updated: 2025/05/30 10:45:12 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_calloc(size_t nmemb, size_t size)
{
    size_t total_size;
    void *ptr;

    total_size = nmemb * size;
    if (total_size == 0)
        return (NULL);
    if (total_size / nmemb != size)
        return (NULL);
    ptr = malloc(total_size);
    if (ptr == NULL)
        return (NULL);
    ft_bzero(ptr, total_size);
    return (ptr);
}