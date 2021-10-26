/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:02:33 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/03 18:02:35 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	if (!c)
		return (ft_strchr(s, '\0'));
	result = 0;
	while (*s)
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	return (result);
}
