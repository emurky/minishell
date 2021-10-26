/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:26:20 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 21:26:23 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var(char *var)
{
	if (!check_env_arg(var))
	{
		printf("minishell: unset: `%s\': not a valid identifier\n", var);
		g_shell.exit_code = 1;
	}
	else
	{
		var_remove(var);
	}
}

bool	mini_unset(char *argv[])
{
	int	i;

	i = 0;
	g_shell.exit_code = 0;
	discard_quotes_in_argv(argv);
	while (argv[i])
		unset_var(argv[i++]);
	return (true);
}
