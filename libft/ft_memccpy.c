/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 04:24:16 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 04:24:19 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	void	*ptr;

	ptr = ft_memchr(src, c, n);
	if (ptr)
	{
		ft_memcpy(dest, src, (char *)ptr - (char *)src + 1);
		return ((char *)ptr - (char *)src + (char *)dest + 1);
	}
	ft_memcpy(dest, src, n);
	return (0);
}
