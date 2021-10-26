/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 00:54:22 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 00:55:15 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

long	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '+')
			sign = 1;
		else
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num > LONG_MAX / 10
			|| (num == LONG_MAX / 10
				&& *str - '0' > LONG_MAX % 10 + (sign == -1)))
			return (num * sign);
		num = 10 * num + (*str++ - '0');
	}
	return (num * sign);
}

long long	ft_atol(const char *str)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '+')
			sign = 1;
		else
			sign = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num > LLONG_MAX / 10
			|| (num == LLONG_MAX / 10
				&& *str - '0' > LLONG_MAX % 10 + (sign == -1)))
			return (num * sign);
		num = 10 * num + (*str++ - '0');
	}
	return (num * sign);
}
