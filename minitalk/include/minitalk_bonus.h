/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:20:44 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/22 12:22:36 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

typedef struct s_server
{
	int				bit_ctr;
	unsigned char	temp_char;
}					t_server;

int		ft_atoi_bonus(const char *str);
void	ft_putstr_fd_bonus(char *s, int fd);
void	ft_putnbr_fd_bonus(int n, int fd);
void	ft_putchar_fd_bonus(char c, int fd);
void	ft_error_exit_bonus(char *msg);

#endif