/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:02:19 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 18:02:23 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	size_t	substr_len;

	substr_len = ft_strlen(s2);
	if (!substr_len)
		return ((char *)s1);
	while (*s2 && size >= substr_len)
	{
		if (size-- < 1 || !*s1)
			return (0);
		if (!ft_memcmp(s1, s2, substr_len))
			return ((char *)s1);
		s1++;
	}
	return (0);
}
