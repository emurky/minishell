/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:06:25 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/26 20:06:27 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_no_redir(char **argv)
{
	if (!argv[0])
		return (false);
	return (!ft_strcmp(argv[0], "exit")
		|| (!ft_strcmp(argv[0], "export") && argv[1])
		|| !ft_strcmp(argv[0], "unset") || !ft_strcmp(argv[0], "cd"));
}

bool	builtin_cmd(t_cmd_line cmd_line)
{
	char	*cmd;

	cmd = cmd_line.argv[0];
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "exit"))
		return (mini_exit(cmd_line.argv));
	if (!ft_strcmp(cmd, "echo"))
		return (mini_echo(cmd_line.argv));
	if (!ft_strcmp(cmd, "cd"))
		return (mini_cd(cmd_line.argv));
	if (!ft_strcmp(cmd, "pwd"))
		return (mini_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (mini_export(cmd_line.argv));
	if (!ft_strcmp(cmd, "unset"))
		return (mini_unset(cmd_line.argv));
	if (!ft_strcmp(cmd, "env"))
		return (mini_env());
	return (false);
}
