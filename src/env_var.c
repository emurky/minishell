/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:51:15 by rkombu            #+#    #+#             */
/*   Updated: 2021/09/17 21:51:19 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_until_var(char **dst_p, char **src_p, bool quotes)
{
	char	*var_start;
	char	*to_append;

	if (quotes)
		var_start = strchr_ignoring_quotes(*src_p, '$');
	else
		var_start = ft_strchr(*src_p, '$');
	if (var_start == NULL)
	{
		*dst_p = append_str(*dst_p, *src_p);
		*src_p = NULL;
		return ;
	}
	to_append = ft_substr(*src_p, 0, var_start - *src_p);
	*dst_p = append_str(*dst_p, to_append);
	free(to_append);
	*src_p = var_start + 1;
}

char	*get_var_name(char **str)
{
	char	*var;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (**str == '?')
	{
		*str += 1;
		return (ft_strdup("?"));
	}
	while (ft_isalnum((*str)[len]) || (*str)[len] == '_')
		len++;
	var = malloc(sizeof(char) * (len + 1));
	var[len] = '\0';
	while (i < len)
	{
		var[i] = (*str)[i];
		i++;
	}
	*str += len;
	return (var);
}

char	*expand(char *var)
{
	char	*expansion;
	size_t	varlen;
	size_t	strlen;
	int		i;

	i = 0;
	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(g_shell.exit_code));
	varlen = ft_strlen(var);
	while (g_shell.envp[i] != NULL)
	{
		if (ft_strncmp(var, g_shell.envp[i], varlen) == 0)
		{
			strlen = ft_strlen(g_shell.envp[i]);
			if (strlen == varlen)
				return (ft_strdup(""));
			if (strlen > varlen && g_shell.envp[i][varlen] == '=')
				break ;
		}
		i++;
	}
	if (g_shell.envp[i] == NULL)
		return (NULL);
	expansion = ft_strdup(g_shell.envp[i] + varlen + 1);
	return (expansion);
}

void	expand_vars(char **str, bool quotes)
{
	char	*result;
	char	*input;
	char	*var;
	char	*expansion;

	input = *str;
	result = ft_strdup("");
	while (*input != '\0')
	{
		copy_until_var(&result, &input, quotes);
		if (input == NULL)
			break ;
		var = get_var_name(&input);
		expansion = expand(var);
		result = append_str(result, expansion);
		free(var);
		free(expansion);
	}
	free(*str);
	*str = result;
}

void	expand_vars_in_redirect(char **str)
{
	char	*result;
	char	*input;
	char	*var;
	char	*expansion;

	input = *str;
	result = ft_strdup("");
	while (*input != '\0')
	{
		copy_until_var(&result, &input, true);
		if (input == NULL)
			break ;
		var = get_var_name(&input);
		expansion = ft_str_truncate(expand(var), ' ');
		if (ft_strchr(expansion, ' '))
		{
			printf("minishell: $%s: ambiguous redirect\n", *str);
			exit(1);
		}
		result = append_str(result, expansion);
		free(var);
		free(expansion);
	}
	free(*str);
	*str = result;
}
