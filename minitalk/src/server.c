/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:20:24 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/18 21:28:42 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static void	handle_char(t_server *server)
{
	if (server->temp_char == '\0')
	{
		ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd(server->temp_char, 1);
	server->bit_ctr = 0;
	server->temp_char = 0;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static t_server	server = {0, 0};
	static pid_t	client_pid = 0;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		server.bit_ctr = 0;
		server.temp_char = 0;
	}
	if (sig == SIGUSR1)
		server.temp_char |= (1 << (7 - server.bit_ctr));
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error_exit("Failed to send acknowledgement signal");
	server.bit_ctr++;
	if (server.bit_ctr == 8)
		handle_char(&server);
}

static void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

int	main(void)
{
	struct sigaction	sa;

	print_pid();
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error_exit("Failed to set SIGUSR1");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error_exit("Failed to set SIGUSR2");
	while (1)
		pause();
	return (0);
}
