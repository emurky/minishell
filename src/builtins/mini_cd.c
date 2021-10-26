/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:25:59 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/19 21:26:04 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_dir_vars(void)
{
	char	*oldpwd;
	char	*pwd;
	char	*cwd;

	oldpwd = expand("OLDPWD");
	pwd = expand("PWD");
	cwd = getcwd(NULL, 0);
	if (pwd)
		var_insert(ft_strjoin("PWD=", cwd));
	if (oldpwd)
	{
		if (!pwd)
			pwd = ft_strdup("");
		var_insert(ft_strjoin("OLDPWD=", pwd));
	}
	free(pwd);
	free(oldpwd);
	free(cwd);
}

bool	mini_cd(char *argv[])
{
	discard_quotes_in_argv(argv);
	g_shell.exit_code = 0;
	if (!argv[1])
		return (true);
	if (chdir(argv[1]) == -1)
	{
		g_shell.exit_code = 1;
		printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
	}
	else
		update_dir_vars();
	return (true);
}
