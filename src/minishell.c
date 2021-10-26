/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:03:42 by rkombu            #+#    #+#             */
/*   Updated: 2021/09/19 21:03:45 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(const char *envp[])
{
	int	i;
	int	index;

	i = 0;
	while (envp[i])
		i++;
	g_shell.env_size = 0;
	g_shell.env_capacity = i * 2;
	g_shell.envp = malloc(sizeof(char *) * g_shell.env_capacity + 1);
	i = 0;
	g_shell.envp[0] = NULL;
	while (envp[i])
	{
		index = var_insert(ft_strdup(envp[i]));
		if (ft_strncmp(g_shell.envp[index], "SHLVL", 5) == 0)
			g_shell.envp[index][6]++;
		i++;
	}
	var_insert(ft_strdup("OLDPWD"));
	g_shell.envp[i] = NULL;
}

static void	shell_init(const char *envp[])
{
	g_shell.shell_state = SHELL;
	g_shell.exit_code = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTERM, SIG_IGN);
	init_envp(envp);
	rl_catch_signals = 0;
}

static bool	str_is_empty(char *str)
{
	while (*str)
		if (!ft_isspace(*str++))
			return (false);
	return (true);
}

int	main(int argc, char *argv[], const char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	shell_init(envp);
	line = NULL;
	while (true)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (!str_is_empty(line))
			add_history(line);
		eval(line);
		free(line);
		line = NULL;
	}
	exit(0);
}
