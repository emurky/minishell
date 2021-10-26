/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 02:08:52 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/05 02:08:55 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s == c)
		s++;
	if (*s)
		num++;
	while (*s)
	{
		s = strchr_ignoring_quotes(s, c);
		if (!s)
			break ;
		while (*s == c)
			s++;
		if (*s)
			num++;
	}
	return (num);
}

static char	*next_word(const char **s, char c)
{
	const char	*start_word;
	const char	*end_word;
	char		*word;

	start_word = *s;
	while (*start_word == c)
		start_word++;
	end_word = strchr_ignoring_quotes(start_word, c);
	if (!end_word)
		end_word = strchr_ignoring_quotes(start_word, 0);
	word = ft_substr(start_word, 0, end_word - start_word);
	*s = end_word;
	return (word);
}

static void	free_array(char **array, int i)
{
	while (i--)
		free(array[i]);
	free(array);
}

char	**ft_split_ignoring_quotes(char const *s, char c)
{
	int		num_words;
	char	**array;
	int		i;

	if (!s)
		return (NULL);
	num_words = count_words(s, c);
	array = malloc(sizeof(char *) * (num_words + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		array[i] = next_word(&s, c);
		if (!array[i])
		{
			free_array(array, i);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
