/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 03:44:27 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/05 03:44:31 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	num_length(int n)
{
	int	num_length;

	if (n == 0)
		return (1);
	num_length = 1;
	if (n > 0)
	{
		num_length--;
		n *= -1;
	}
	while (n < 0)
	{
		num_length++;
		n /= 10;
	}
	return (num_length);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		length;

	length = num_length(n);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
		str[0] = '-';
	else
		n *= -1;
	str[length--] = 0;
	while (n < 0)
	{
		str[length--] = -(n % 10) + '0';
		n /= 10;
	}
	return (str);
}
