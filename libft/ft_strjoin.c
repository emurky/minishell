/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:47:46 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/05 00:47:47 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	char	*dst;

	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(length);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst + ft_strlcpy(dst, s1, length), s2, length);
	return (dst);
}

char	*append_str(char *s1, char const *s2)
{
	char	*dst;

	if (s2 == NULL)
		return (s1);
	dst = ft_strjoin(s1, s2);
	free(s1);
	return (dst);
}
