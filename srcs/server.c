/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:48:50 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/24 12:24:53 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char g_buffer[4096] = {0};

static void	handler(int signal_num)
{
	static unsigned char	mask = 0b10000000;
	static int				i = 0;

	if (signal_num == SIGUSR1)
		g_buffer[i] += mask;
	mask = mask >> 1;
	if (mask == 0)
	{
		if (byte != '\0')
		{
			write(STDOUT_FILENO, &byte, 1);
		else
			ft_putstr_fd("\nMessage received\n", STDOUT_FILENO);
		mask = 0b10000000;
		byte = 0;
		pause();
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &handler;
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
		/* pause(); */
	}
	return (0);
}
