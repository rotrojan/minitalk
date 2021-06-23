/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bigo <rotrojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:51:06 by rotrojan          #+#    #+#             */
/*   Updated: 2021/06/23 20:28:32 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

int		ft_atoi(char const *str);
int		ft_isdigit(int c);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(char const *str);
void	ft_bzero(void *b, size_t n);
void	*ft_memset(void *b, int c, size_t len);

#endif
