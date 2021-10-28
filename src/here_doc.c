/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:48:18 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/18 21:48:23 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_if(void *file)
{
	if (((t_file *)file)->type == HERE_DOC)
		handle_heredoc(file);
}

void	handle_heredoc(t_file *file)
{
	int	fd;

	if (file->delimiter)
	{
		fd = open(file->filename, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		expand_here_doc(fd, file->delimiter);
		close(fd);
	}
}

bool	read_here_docs(t_parser *parser)
{
	int		i;
	pid_t	pid;
	int		status;

	assign_heredoc_filename(parser);
	i = 0;
	pid = ft_fork();
	g_shell.shell_state = HERE_DOC_READING;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		while (i < parser->num_cmd)
			ft_lstiter(parser->cmd_lines[i++].infiles, expand_if);
		exit(0);
	}
	if (waitpid(pid, &status, 0) != pid)
	{
		printf("wait for heredoc process error: %s\n", strerror(errno));
		exit(1);
	}
	g_shell.shell_state = SHELL;
	if (WIFSIGNALED(status))
		return (clean_here_docs(parser));
	return (true);
}

void	expand_here_doc(int fd_here_doc, char *delimeter)
{
	ssize_t	bytes_to_write;
	char	*line;

	bytes_to_write = 0;
	while (true)
	{
		line = readline("> ");
		if (!line)
			line = ft_strdup("");
		if (ft_strcmp(line, delimeter) == 0 || bytes_to_write > 4096)
			break ;
		if (ft_strchr(line, '$'))
			expand_vars(&line, false);
		bytes_to_write += ft_strlen(line) + 1;
		ft_putstr_fd(line, fd_here_doc);
		ft_putstr_fd("\n", fd_here_doc);
		free(line);
		line = NULL;
	}
	close(fd_here_doc);
}
