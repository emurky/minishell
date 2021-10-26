/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 04:16:58 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 04:17:01 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return ('a' + c - 'A');
	else
		return (c);
}

void	ft_str_tolower(char *str)
{
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}
