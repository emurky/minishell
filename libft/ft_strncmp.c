/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:02:00 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 18:02:08 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
		if (*s1++ != *s2++ || !*(s1 - 1))
			return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
	return (0);
}

int	ft_strcmp(const char *l, const char *r)
{
	while (*l == *r && *l)
	{
		l++;
		r++;
	}
	return (*(unsigned char *)l - *(unsigned char *)r);
}
