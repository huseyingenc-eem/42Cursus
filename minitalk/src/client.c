
#include "../include/minitalk.h"

static volatile int	g_signal_received = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_signal_received = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Message received by server!\n", 1);
		exit(0);
	}
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_signal_received = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1); // 1 biti gönder
		else
			kill(pid, SIGUSR2); // 0 biti gönder
		while (!g_signal_received)
			usleep(100); // Server'dan onay (ACK) gelene kadar bekle
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	if (argc != 3)
		ft_error_exit("Usage: ./client <PID> <MESSAGE>");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_error_exit("Invalid PID");
	signal(SIGUSR1, ack_handler);
	signal(SIGUSR2, ack_handler);
	i = 0;
	while (argv[2][i])
	{
		send_char(server_pid, (unsigned char)argv[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}