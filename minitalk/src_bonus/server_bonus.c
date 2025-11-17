#include "minitalk_bonus.h"

static t_server	g_server;

static void	process_bit(int signal)
{
    if (signal == SIGUSR1)
        g_server.character <<= 1;
    else if (signal == SIGUSR2)
        g_server.character = (g_server.character << 1) | 1;
}

static void	handle_complete_character(void)
{
    static int	byte_count = 0;

    if (g_server.character == 0)
    {
        ft_putchar('\n');
        ft_putnbr(byte_count);
        ft_putstr(" bytes received\n");
        if (kill(g_server.client_pid, SIGUSR2) == -1)
            exit(1);
        byte_count = 0;
    }
    else
    {
        ft_putchar(g_server.character);
        byte_count++;
        if (kill(g_server.client_pid, SIGUSR1) == -1)
            exit(1);
    }
    g_server.character = 0;
    g_server.bit_count = 0;
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
    (void)context;
    g_server.client_pid = info->si_pid;
    process_bit(signal);
    g_server.bit_count++;
    if (g_server.bit_count == 8)
        handle_complete_character();
    else if (kill(g_server.client_pid, SIGUSR1) == -1)
        exit(1);
}

static void	setup_and_run(void)
{
    struct sigaction	sa;
    pid_t				pid;

    pid = getpid();
    ft_putstr("Server PID: ");
    ft_putnbr(pid);
    ft_putstr("\nWaiting for messages...\n");
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sa.sa_sigaction = signal_handler;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
        exit(1);
    while (1)
        pause();
}

int	main(void)
{
    g_server.character = 0;
    g_server.bit_count = 0;
    g_server.client_pid = 0;
    setup_and_run();
    return (0);
}