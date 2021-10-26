/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 04:25:05 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 04:25:09 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_copy;
	const char	*src_copy;

	if (!src && !dest)
		return (0);
	dest_copy = dest;
	src_copy = src;
	while (n--)
		*dest_copy++ = *src_copy++;
	return (dest);
}
