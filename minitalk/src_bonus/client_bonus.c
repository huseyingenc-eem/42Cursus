/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:20:29 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/18 21:22:32 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd_bonus("Message successfully delivered!\n", 1);
		exit(0);
	}
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		g_ack = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			pause();
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
		ft_error_exit_bonus("Usage: ./client_bonus <PID> <MESSAGE>");
	server_pid = ft_atoi_bonus(argv[1]);
	if (server_pid <= 0)
		ft_error_exit_bonus("Invalid PID");
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error_exit_bonus("Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error_exit_bonus("Failed to set SIGUSR2 handler");
	i = -1;
	while (argv[2][++i])
		send_char(server_pid, (unsigned char)argv[2][i]);
	send_char(server_pid, '\0');
	while (1)
		pause();
	return (0);
}
