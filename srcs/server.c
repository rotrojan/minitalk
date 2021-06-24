/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:48:50 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/24 15:56:11 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signal_num, siginfo_t *info, void *context)
{
	static unsigned char	mask = 0b10000000;
	static unsigned char	byte = 0;

	(void)context;
	if (signal_num == SIGUSR1)
		byte += mask;
	mask = mask >> 1;
	if (mask == 0)
	{
		if (byte != '\0')
			write(STDOUT_FILENO, &byte, 1);
		else
		{
			ft_putstr_fd("\nMessage received\n", STDOUT_FILENO);
			if (kill(info->si_pid, SIGUSR1) == -1)
				exit_error("Reception acknowledgment not sent\n");
		}
		mask = 0b10000000;
		byte = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac != 1)
	{
		ft_putstr_fd("Usage: ./server\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd("Minitalk: Server running\nPID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (1)
	{
		pause();
	}
	return (0);
}
