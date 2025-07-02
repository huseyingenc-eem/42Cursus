/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc@student.42kocaeli.com.tr <hgenc@s    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:17:04 by hgenc@stude       #+#    #+#             */
/*   Updated: 2025/07/02 11:17:04 by hgenc@stude      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *format, ...);

int		ft_putchar_len(char c);
int		ft_putstr_len(char *str);
int		ft_putnbr_len(int n);
int		ft_puthex_len(unsigned long long n, int is_upper);
int		ft_putptr_len(unsigned long long ptr);

#endif
