/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:41:36 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/23 21:41:39 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_capacity(void)
{
	int		i;
	char	**new_envp;

	i = 0;
	g_shell.env_capacity *= 2;
	new_envp = malloc(sizeof(char *) * g_shell.env_capacity + 1);
	new_envp[i] = g_shell.envp[i];
	while (g_shell.envp[i++])
		new_envp[i] = g_shell.envp[i];
	free(g_shell.envp);
	g_shell.envp = new_envp;
}

int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

int	var_insert(char *var)
{
	int	index;
	int	i;
	int	len;

	if (g_shell.env_size == g_shell.env_capacity)
		expand_capacity();
	len = get_var_name_len(var);
	index = 0;
	while (g_shell.envp[index]
		&& ft_strncmp(g_shell.envp[index], var, len) < 0)
		index++;
	if (g_shell.envp[index] && ft_strncmp(g_shell.envp[index], var, len) == 0)
		free(g_shell.envp[index]);
	else
	{
		i = g_shell.env_size;
		while (i > index)
		{
			g_shell.envp[i] = g_shell.envp[i - 1];
			i--;
		}
		g_shell.envp[++g_shell.env_size] = NULL;
	}
	g_shell.envp[index] = var;
	return (index);
}

void	var_remove(char *var)
{
	int	i;
	int	name_len;

	name_len = get_var_name_len(var);
	i = 0;
	while (g_shell.envp[i] && ft_strncmp(g_shell.envp[i], var, name_len) < 0)
		i++;
	if (g_shell.envp[i] && ft_strncmp(g_shell.envp[i], var, name_len) == 0)
	{
		free(g_shell.envp[i]);
		while (g_shell.envp[i])
		{
			g_shell.envp[i] = g_shell.envp[i + 1];
			i++;
		}
		g_shell.env_size--;
	}
}
