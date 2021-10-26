/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:24:32 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/04 21:24:35 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	size_t	length;
	char	*dst;

	length = ft_strlen(src);
	dst = malloc(length + 1);
	if (!dst)
		return (NULL);
	return (ft_memcpy(dst, src, length + 1));
}
