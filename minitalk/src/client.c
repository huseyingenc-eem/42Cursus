/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:19:56 by hgenc             #+#    #+#             */
/*   Updated: 2025/11/18 21:19:30 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static void	ack_handler(int sig)
{
	(void)sig;
}

static int	get_server_pid(char *arg)
{
	int	i;
	int	pid;

	i = 0;
	if (!arg || !arg[0])
		ft_error_exit("Invalid PID");
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			ft_error_exit("Invalid PID");
		i++;
	}
	pid = ft_atoi(arg);
	if (pid <= 0 || kill(pid, 0) == -1)
		ft_error_exit("Invalid PID");
	return (pid);
}

static void	send_char(int pid, unsigned char c)
{
	int	i;
	int	sig;

	i = 8;
	while (--i >= 0)
	{
		sig = SIGUSR1;
		if (!((c >> i) & 1))
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
			ft_error_exit("Failed to send signal");
		pause();
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
		ft_error_exit("Usage: ./client <PID> <MESSAGE>");
	server_pid = get_server_pid(argv[1]);
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error_exit("Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error_exit("Failed to set SIGUSR2 handler");
	i = 0;
	while (argv[2][i])
	{
		send_char(server_pid, (unsigned char)argv[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
