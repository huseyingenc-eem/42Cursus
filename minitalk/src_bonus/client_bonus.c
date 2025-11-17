#include "minitalk_bonus.h"

static t_client	g_client;

void	client_handler(int signal)
{
    if (signal == SIGUSR1)
        g_client.received_signal = 1;
    else if (signal == SIGUSR2)
    {
        ft_putchar('\n');
        exit(0);
    }
}

static void	send_bit_and_wait(pid_t pid, int bit)
{
    g_client.received_signal = 0;
    if (kill(pid, bit ? SIGUSR2 : SIGUSR1) == -1)
        exit(1);
    while (!g_client.received_signal)
        pause();
}

static void	send_char_bits(pid_t pid, unsigned char c)
{
    int	bit_index;

    bit_index = 7;
    while (bit_index >= 0)
    {
        send_bit_and_wait(pid, (c >> bit_index) & 1);
        bit_index--;
    }
}

static void	send_message(pid_t pid, char *message)
{
    int	i;

    i = 0;
    ft_putstr("Sending message");
    while (message[i])
    {
        send_char_bits(pid, message[i]);
        i++;
    }
    send_char_bits(pid, 0);
}

int	main(int argc, char **argv)
{
    pid_t	server_pid;

    if (argc != 3)
    {
        ft_putstr("Usage: ./client_bonus <server_pid> <message>\n");
        return (1);
    }
    server_pid = ft_atoi(argv[1]);
    if (server_pid <= 0 || kill(server_pid, 0) == -1)
    {
        ft_putstr("Error: Invalid PID\n");
        return (1);
    }
    g_client.server_pid = server_pid;
    g_client.received_signal = 0;
    signal(SIGUSR1, client_handler);
    signal(SIGUSR2, client_handler);
    send_message(server_pid, argv[2]);
    while (1)
        pause();
    return (0);
}