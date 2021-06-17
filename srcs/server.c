/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:48:50 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/17 21:01:28 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signal_num)
{
	static unsigned char	mask = 0b10000000;
	static unsigned char	byte = 0;

	if (signal_num == SIGUSR1)
		byte += mask;
	mask = mask >> 1;
	if (mask == 0)
	{
		if (byte != '\0')
			write(STDOUT_FILENO, &byte, 1);
		else
			ft_putstr_fd("\nString received.\n", STDOUT_FILENO);
		mask = 0b10000000;
		byte = 0;
	}
}

int	main(int ac, char **av)
{
	(void)av;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
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
