/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:02:24 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/14 12:58:40 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 4096

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*read_file(const char *path);
char	**split_lines(char *text, size_t *line_count);
int		has_ber_extension(const char *path);
void	error_exit(const char *message);
int		ft_printf(const char *format, ...);

#endif
