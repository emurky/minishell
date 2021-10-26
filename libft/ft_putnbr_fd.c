/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:43:26 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/05 04:43:28 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	number[10];
	int		i;

	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
		ft_putchar_fd('-', fd);
	else
		n *= -1;
	i = 0;
	while (n < 0)
	{
		number[i++] = -(n % 10) + '0';
		n /= 10;
	}
	while (i--)
		ft_putchar_fd(number[i], fd);
}
