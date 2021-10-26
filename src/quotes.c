/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:13:39 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/16 20:13:42 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_single_qoutes(char *str, int *i_p)
{
	int		i;

	i = *i_p;
	str[i] = '\0';
	str = append_str(str, str + i + 1);
	while (str[i + 1] && str[i] != '\'')
		i++;
	str[i] = '\0';
	str = append_str(str, str + i + 1);
	*i_p = i - 1;
	return (str);
}

static char	*process_double_qoutes(char *str, int *i_p)
{
	int		i;
	char	*cur;
	char	*var;
	char	*expansion;

	i = *i_p;
	str[i] = '\0';
	str = append_str(str, str + i + 1);
	while (str[i + 1] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			cur = str + i + 1;
			str[i] = '\0';
			var = get_var_name(&cur);
			expansion = expand(var);
			str = append_str(append_str(str, expansion), cur);
			i += ft_strlen(expansion);
			free(var);
			free(expansion);
		}
		else
			i++;
	}
	str[i] = '\0';
	str = append_str(str, str + i + 1);
	*i_p = i - 1;
	return (str);
}

void	discard_quotes_in_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		discard_quotes(argv + i);
		i++;
	}
}

void	discard_quotes(char **str)
{
	char	*result;
	int		i;

	result = *str;
	i = 0;
	while (result[i])
	{
		if (result[i] == '\'')
			result = process_single_qoutes(result, &i);
		else if (result[i] == '\"')
			result = process_double_qoutes(result, &i);
		i++;
	}
	*str = result;
}
