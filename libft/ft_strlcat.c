/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:00:36 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 18:00:44 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;

	dest_len = 0;
	while (size && *dst)
	{
		size--;
		dst++;
		dest_len++;
	}
	if (!size)
		return (dest_len + ft_strlen(src));
	return (dest_len + ft_strlcpy(dst, src, size));
}
