/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:39:57 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/17 21:39:14 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	ft_strlen(char const *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		++size;
	return (size);
}

void	ft_putstr_fd(char const *str, int fd)
{
	write(fd, str, ft_strlen(str));
}
