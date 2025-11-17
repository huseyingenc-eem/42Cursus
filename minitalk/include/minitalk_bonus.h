#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# define _GNU_SOURCE
# define _POSIX_C_SOURCE 200809L

# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_server
{
	unsigned char	character;
	int				bit_count;
	pid_t			client_pid;
}					t_server;

typedef struct s_client
{
	int				received_signal;
	pid_t			server_pid;
}					t_client;

void				signal_handler(int signal, siginfo_t *info, void *context);
void				client_handler(int signal);
void				send_bit(pid_t pid, int bit);
void				send_char(pid_t pid, unsigned char c);
void				send_string(pid_t pid, char *str);
void				print_pid(void);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(int n);
int					ft_atoi(const char *str);

#endif