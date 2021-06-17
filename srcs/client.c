/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:48:50 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/17 21:00:58 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bool	check_errors(int ac, char **av)
{
	int	i;

	if (ac != 3)
		return (FALSE);
	i = 0;
	while (av[1][i])
	{
		if (ft_isdigit(av[1][i]) == FALSE)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	send_byte(int server_pid, char byte)
{
	unsigned char	mask;
	unsigned char	bit;

	mask = 0b10000000;
	while (mask != 0b00000000)
	{
		bit = 0;
		bit = byte & mask;
		if (bit != 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(10);
		mask = mask >> 1;
	}
}

void	send_str(int server_pid, const char *str)
{
	char	*ptr;

	ptr = (char *)str;
	while (*ptr)
	{
		send_byte(server_pid, *ptr);
		++ptr;
	}
	send_byte(server_pid, *ptr);
}

int	main(int ac, char **av)
{
	if (check_errors(ac, av) == FALSE)
	{
		ft_putstr_fd("Usage:   ./client <server_pid> <message>\n",
			STDERR_FILENO);
		ft_putstr_fd("Example: ./client 42424 \"Hello world!\"\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	send_str(ft_atoi(av[1]), av[2]);
	return (EXIT_SUCCESS);
}
