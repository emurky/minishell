/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 02:38:49 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 02:38:53 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

int	ft_isnumstr(char *str)
{
	if (*str == '+' || *str == '-')
	{
		str++;
		if (!*str)
			return (0);
	}
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}
