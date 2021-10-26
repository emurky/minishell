/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:26:07 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 21:26:11 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_env_arg(char *str)
{
	int	i;

	if (!(ft_isalpha(*str) || *str == '_'))
		return (false);
	i = 1;
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (false);
		str++;
	}
	return (true);
}

static void	print_env(void)
{
	int		i;
	char	*eq_sign;

	i = 0;
	while (g_shell.envp[i])
	{
		eq_sign = ft_strchr(g_shell.envp[i], '=');
		if (!eq_sign)
			printf("declare -x %s\n", g_shell.envp[i]);
		else
		{
			write(STDOUT_FILENO, "declare -x ", 11);
			write(STDOUT_FILENO, g_shell.envp[i],
				eq_sign - g_shell.envp[i] + 1);
			printf("\"%s\"\n", eq_sign + 1);
		}
		i++;
	}
}

static void	export_var(char *var)
{
	if (!check_env_arg(var))
	{
		printf("minishell: export: `%s\': not a valid identifier\n", var);
		g_shell.exit_code = 1;
	}
	else
	{
		var_insert(ft_strdup(var));
	}
}

bool	mini_export(char *argv[])
{
	int	i;

	i = 1;
	g_shell.exit_code = 0;
	discard_quotes_in_argv(argv);
	if (!argv[1])
		print_env();
	else
		while (argv[i])
			export_var(argv[i++]);
	return (true);
}
