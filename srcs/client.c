/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:48:50 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/24 16:05:01 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#define MAX_LEN_PID_STR 7

static void	handler(int signal_num, siginfo_t *info, void *context)
{
	(void)signal_num;
	(void)context;
	ft_putstr_fd("Message received and displayed by server ", STDOUT_FILENO);
	ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

static t_bool	check_errors(int ac, char **av)
{
	int	i;

	if (ac != 3)
		return (FALSE);
	if (ft_atoi(av[1]) < 1 || ft_strlen(av[1]) > MAX_LEN_PID_STR)
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

static void	send_byte(int server_pid, char byte)
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
		usleep(100);
		mask = mask >> 1;
	}
}

static void	send_str(int server_pid, const char *str)
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
	pid_t				pid;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	ft_bzero(&sa, sizeof(sa));
	if (check_errors(ac, av) == FALSE)
	{
		ft_putstr_fd("Usage:   ./client <server_pid> <message>\n",
			STDERR_FILENO);
		ft_putstr_fd("Example: ./client 42424 \"Hello world!\"\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	pid = (pid_t)ft_atoi(av[1]);
	send_str(pid, av[2]);
	ft_putstr_fd("Waiting for reception acknowledgment ...\n", STDOUT_FILENO);
	sleep(3);
	ft_putstr_fd("Reception acknowledgment not received\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
