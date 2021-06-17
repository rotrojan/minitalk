/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:44:29 by rotrojan          #+#    #+#             */
/*   Updated: 2019/11/01 19:56:32 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char		*str;
	size_t		len;

	len = ft_strlen(s1) + 1;
	if (!(str = (char*)malloc(sizeof(*s1) * len)))
		return (NULL);
	return ((char*)ft_memcpy(str, s1, len));
}
