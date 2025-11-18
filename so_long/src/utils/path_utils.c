/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:34:18 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/11 15:47:20 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	has_ber_extension(const char *path)
{
	int	path_length;
	int	index;

	if (!path)
		return (FALSE);
	path_length = ft_strlen(path);
	if (path_length < 5)
		return (FALSE);
	if (ft_strncmp(&path[path_length - 4], ".ber", 4) != 0)
		return (FALSE);
	index = path_length - 5;
	while (index > 0 && path[index] != '/')
		index--;
	if (path[index] == '/')
		index++;
	if (index == path_length - 4)
		return (FALSE);
	return (TRUE);
}
