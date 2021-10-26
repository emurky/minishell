/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:02:57 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/26 20:02:58 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_child_processes(pid_t last_cmd_pid)
{
	int	status;

	status = 0;
	waitpid(last_cmd_pid, &status, 0);
	while (true)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	}
	g_shell.shell_state = SHELL;
	g_shell.exit_code = WEXITSTATUS(status);
}

void	eval(char *line)
{
	t_parser	*parser;
	pid_t		last_cmd_pid;

	parser = parse_input(line);
	if (!parser || !read_here_docs(parser))
		return ;
	last_cmd_pid = 0;
	if (parser->num_cmd == 1 && builtin_no_redir(parser->cmd_lines[0].argv))
		run_command(parser->cmd_lines[0], STDIN_FILENO, STDOUT_FILENO);
	else if (parser->num_cmd > 1
		|| parser->cmd_lines[0].infiles || parser->cmd_lines[0].outfiles
		|| !builtin_cmd(parser->cmd_lines[0]))
	{
		run_pipeline(parser, &last_cmd_pid);
		wait_for_child_processes(last_cmd_pid);
	}
	free_parser(parser, false, 0);
}

static int	set_up_output_fd(t_parser *parser, int i, int pipe[2])
{
	if (i < parser->num_cmd - 1)
	{
		ft_pipe(pipe);
		return (pipe[1]);
	}
	else
		return (STDOUT_FILENO);
}

void	run_pipeline(t_parser *parser, pid_t *last_cmd_pid)
{
	int	i;
	int	in;
	int	out;
	int	pipe[2];

	in = STDIN_FILENO;
	i = 0;
	while (i < parser->num_cmd)
	{
		out = set_up_output_fd(parser, i, pipe);
		*last_cmd_pid = ft_fork();
		if (*last_cmd_pid == 0)
		{
			if (i < parser->num_cmd - 1)
				close(pipe[0]);
			rl_clear_history();
			run_command(parser->cmd_lines[i], in, out);
		}
		if (i > 0)
			close(in);
		in = pipe[0];
		if (i < parser->num_cmd - 1)
			close(pipe[1]);
		i++;
	}
}
