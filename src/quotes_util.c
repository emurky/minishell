/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:51:29 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/26 20:51:32 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strchr_ignoring_quotes(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				return (NULL);
		}
		if (!*s++)
			return (NULL);
	}
	return ((char *)s);
}

char	*strchr_ignoring_single_quotes(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\'')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				return (NULL);
		}
		if (!*s++)
			return (NULL);
	}
	return ((char *)s);
}

unsigned int	strcspn_ignoring_quotes(const char *s, const char *charset)
{
	const char	*pos;

	if ((s == NULL) || (charset == NULL))
		return (0);
	pos = s;
	while (*pos)
	{
		if (*pos == '\'' || *pos == '\"')
		{
			pos = ft_strchr(pos + 1, *pos);
			if (!pos)
				return (ft_strlen(s));
			pos++;
		}
		if (ft_strchr(charset, *pos))
			return (pos - s);
		else
			pos++;
	}
	return (pos - s);
}
