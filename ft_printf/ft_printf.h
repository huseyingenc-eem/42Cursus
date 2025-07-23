/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:38:21 by hgenc             #+#    #+#             */
/*   Updated: 2025/07/03 16:06:50 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int		ft_printf(const char *format, ...);
int		ft_putchar_len(char c);
int		ft_putstr_len(char *str);
int		ft_putnbr_len(int n);
int		ft_puthex_len(unsigned long n, int is_upper);
int		ft_putptr_len(unsigned long ptr);

#endif