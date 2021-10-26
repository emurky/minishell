/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_truncate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:09:54 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/16 19:09:56 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_truncate(char *str, char c)
{
	int		start;
	int		end;
	char	*result;

	if (!str)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] == c)
		start++;
	while (end && str[end - 1] == c)
		end--;
	str[end] = '\0';
	result = ft_strdup(str + start);
	free(str);
	return (result);
}
