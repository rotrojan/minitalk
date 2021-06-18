/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:48:50 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/18 03:01:39 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#define MAX_LEN_PID_STR 7

void	exit_error(char const *error_msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

t_bool	check_errors(int ac, char **av, pid_t pid)
{
	int	i;

	if (ac != 3)
		return (FALSE);
	if (pid < 1 || ft_strlen(av[1]) > MAX_LEN_PID_STR)
	{
		ft_putstr_fd("Error: invalid PID\n", STDERR_FILENO);
		return (FALSE);
	}
	i = 0;
	while (av[1][i])
	{
		if (ft_isdigit(av[1][i]) == FALSE)
		{
			ft_putstr_fd("Error: invalid PID\n", STDERR_FILENO);
			return (FALSE);
		}
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
		{
			if (kill(server_pid, SIGUSR1) == -1)
				exit_error("signal not sent\n");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				exit_error("signal not sent\n");
		}
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
	pid_t	pid;

	pid = (pid_t)ft_atoi(av[1]);
	if (check_errors(ac, av, pid) == FALSE)
	{
		ft_putstr_fd("Usage:   ./client <server_pid> <message>\n",
			STDERR_FILENO);
		ft_putstr_fd("Example: ./client 42424 \"Hello world!\"\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	send_str(pid, av[2]);
	return (EXIT_SUCCESS);
}
