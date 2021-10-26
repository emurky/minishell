/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:21:20 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 17:21:23 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numerical(char *str)
{
	if (!ft_isdigit(*str) && *str != '-' && *str != '+')
		return (false);
	str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (false);
	return (true);
}

static bool	check_overflow(char *str)
{
	if (*str == '-')
		return (ft_strcmp(str + 1, "9223372036854775808") <= 0);
	if (*str == '+')
		return (ft_strcmp(str + 1, "9223372036854775807") <= 0);
	return (ft_strcmp(str, "9223372036854775807") <= 0);
}

bool	mini_exit(char *argv[])
{
	if (!argv[1])
		exit(g_shell.exit_code);
	if (!is_numerical(argv[1]) || !check_overflow(argv[1]))
	{
		if (g_shell.shell_state == SHELL)
			printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(255);
	}
	if (argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_shell.exit_code = 1;
	}
	else
	{
		if (g_shell.shell_state == SHELL)
			printf("exit\n");
		exit(ft_atol(argv[1]));
	}
	return (true);
}
