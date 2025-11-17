/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* server.c                                           :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: 42Student <student@42.fr>                  +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/17 10:00:00 by 42Student         #+#    #+#             */
/* Updated: 2025/11/17 10:00:00 by 42Student        ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../include/minitalk.h"

/*
** Server için global değişkene ihtiyacımız yok gibi görünse de, 
** Norminette kuralları gereği statik değişkenleri fonksiyon içinde tutmak 
** daha temizdir. Ancak sinyal işleyicilerde veri bütünlüğü için
** bu yapıyı kullanıyoruz.
*/

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_ctr = 0;
	static unsigned char	temp_char = 0;

	(void)context;
	if (sig == SIGUSR1)
		temp_char |= (1 << (7 - bit_ctr));
	bit_ctr++;
	if (bit_ctr == 8)
	{
		if (temp_char == '\0')
		{
			ft_putchar_fd('\n', 1);
			kill(info->si_pid, SIGUSR2); // Mesaj bitti onayı
		}
		else
			ft_putchar_fd(temp_char, 1);
		bit_ctr = 0;
		temp_char = 0;
	}
	kill(info->si_pid, SIGUSR1); // "Bir sonraki biti gönder" onayı
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
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