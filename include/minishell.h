/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurky <emurky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:58:41 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/28 18:25:42 by emurky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/pipe.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "parser.h"

typedef enum e_state {SHELL, FOREGROUNG_JOB, HERE_DOC_READING}	t_state;

typedef struct s_shell
{
	t_state	shell_state;
	int		exit_code;
	char	**envp;
	int		env_size;
	int		env_capacity;
}			t_shell;

typedef struct s_var
{
	char	*key;
	char	*value;
}			t_var;

t_shell	g_shell;

void	eval(char *line);
bool	builtin_cmd(t_cmd_line cmd_line);
bool	builtin_no_redir(char **argv);
void	run_pipeline(t_parser *parser, pid_t *last_cmd_pid);
void	run_command(t_cmd_line cmd, int in, int out);
int		set_up_input(int in, t_list *infiles);
int		set_up_output(int out, t_list *outfiles, bool is_exit);
int		check_infile(t_file *file);
int		create_outfile(t_file *file);
char	*full_path(char *command);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
pid_t	ft_fork(void);
int		ft_pipe(int pipefd[2]);
int		print_error(char *msg, int exit_code);
bool	mini_echo(char *argv[]);
bool	mini_exit(char *argv[]);
bool	mini_cd(char *argv[]);
bool	mini_pwd(void);
bool	mini_export(char *argv[]);
bool	mini_unset(char *argv[]);
bool	mini_env(void);
int		var_insert(char *var);
void	var_remove(char *var);
int		get_var_name_len(char *str);
bool	check_env_arg(char *str);

#endif
