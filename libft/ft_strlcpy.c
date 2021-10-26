/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:01:05 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 18:01:07 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	char	*dst_start;

	if (!src || !dst)
		return (0);
	dst_start = dst;
	if (maxlen--)
	{
		while (maxlen && *src)
		{
			*dst++ = *src++;
			maxlen--;
		}
		*dst = '\0';
	}
	return (dst - dst_start + ft_strlen(src));
}
