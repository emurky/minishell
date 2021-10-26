/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:36:57 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/04 22:36:59 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	max_length;
	char	*dst;

	max_length = ft_strlen(s);
	if (max_length < start)
		return (ft_strdup(""));
	max_length -= start;
	if (max_length > len)
		max_length = len;
	dst = malloc(max_length + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s + start, max_length);
	*(dst + max_length) = 0;
	return (dst);
}
