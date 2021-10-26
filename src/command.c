/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 00:27:59 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/16 00:28:05 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_cmd_line cmd, int in, int out)
{
	if (set_up_input(in, cmd.infiles) == -1)
		return ;
	if (set_up_output(out, cmd.outfiles, builtin_no_redir(cmd.argv)) == -1)
		return ;
	discard_quotes_in_argv(cmd.argv);
	if (cmd.argv[0] && !builtin_cmd(cmd))
	{
		execve(full_path(cmd.argv[0]), cmd.argv, (char *const *)g_shell.envp);
		perror(cmd.argv[0]);
	}
	if (g_shell.shell_state == FOREGROUNG_JOB)
		exit(g_shell.exit_code);
}

int	set_up_input(int in, t_list *infiles)
{
	char	**filename_p;

	dup2(in, STDIN_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	while (infiles)
	{
		filename_p = &((t_file *)infiles->content)->filename;
		expand_vars_in_redirect(filename_p);
		discard_quotes(filename_p);
		in = check_infile(infiles->content);
		if (in == -1)
			return (-1);
		dup2(in, STDIN_FILENO);
		close(in);
		infiles = infiles->next;
	}
	return (in);
}

int	set_up_output(int out, t_list *outfiles, bool is_exit)
{
	char	**filename_p;

	if (!is_exit)
		dup2(out, STDOUT_FILENO);
	if (out != STDOUT_FILENO)
		close(out);
	while (outfiles)
	{
		filename_p = &((t_file *)outfiles->content)->filename;
		expand_vars_in_redirect(filename_p);
		discard_quotes(filename_p);
		out = create_outfile(outfiles->content);
		if (out == -1)
			return (-1);
		if (!is_exit)
			dup2(out, STDOUT_FILENO);
		close(out);
		outfiles = outfiles->next;
	}
	return (out);
}
