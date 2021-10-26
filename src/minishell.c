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
		// if (*line)
		if (!str_is_empty(line))
			add_history(line);
		//
		// if (!strcmp(line, "exit")) { free(line); exit(0);}
		//

		eval(line);
		free(line);
		line = NULL;
	}
	exit(0);
}

/*
static void print_file(void *p)
{
	t_file	*file = p;
	if (file->type == HERE_DOC)
		printf("		_%s_	%u	delimiter = _%s_\n",
			file->filename, file->type, file->delimiter);
	else
		printf("		_%s_	%u\n", file->filename, file->type);
}
*/

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
	// int			i; //

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


	/* debugging */
	/*
	i = 0;
	printf("\n\n	Check-up:\n");
	while (i < parser->num_cmd)
	{
		printf("%d. %s\n", i, parser->cmd_list[i]);
		printf("	Infiles:\n");
		ft_lstiter(parser->cmd_lines[i].infiles, print_file);
		printf("	Outfiles:\n");
		ft_lstiter(parser->cmd_lines[i].outfiles, print_file);
		char **ft_argv = parser->cmd_lines[i].argv;
		printf("	Argv:\n");
		for (int j = 0; ft_argv[j]; j++)
			printf("		%d. _%s_\n", j, ft_argv[j]);
		i++;
	}
	printf("exit code: %d\n", shell.exit_code);
	*/
	/* end of debugging */

	free_parser(parser, false, 0);
}

bool	builtin_no_redir(char **argv)
{
	if (!argv[0])
		return(false);
	return (!ft_strcmp(argv[0], "exit")
		|| (!ft_strcmp(argv[0], "export") && argv[1])
		|| !ft_strcmp(argv[0], "unset") || !ft_strcmp(argv[0], "cd"));
}

bool	builtin_cmd(t_cmd_line cmd_line)
{
	char *cmd;

	cmd = cmd_line.argv[0];

	if (!cmd)
		return(false);
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
		if (i < parser->num_cmd - 1)
		{
			ft_pipe(pipe);
			out = pipe[1];
		}
		else
			out = STDOUT_FILENO;
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
