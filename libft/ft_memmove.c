/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 04:25:20 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 04:25:23 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_copy;
	const char	*src_copy;

	src_copy = src;
	dest_copy = dest;
	if (dest_copy == src_copy)
		return (dest_copy);
	if (dest_copy < src_copy)
		while (n--)
			*dest_copy++ = *src_copy++;
	else
	{
		dest_copy += n;
		src_copy += n;
		while (n--)
			*--dest_copy = *--src_copy;
	}
	return (dest);
}
