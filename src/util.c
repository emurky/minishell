/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 03:06:37 by rkombu            #+#    #+#             */
/*   Updated: 2021/09/16 03:06:44 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strchr_ignoring_quotes(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\'' || *s == '\"')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				return (NULL);
		}
		if (!*s++)
			return (NULL);
	}
	return ((char *)s);
}

char	*strchr_ignoring_single_quotes(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\'')
		{
			s = ft_strchr(s + 1, *s);
			if (!s)
				return (NULL);
		}
		if (!*s++)
			return (NULL);
	}
	return ((char *)s);
}

unsigned int	strcspn_ignoring_quotes(const char *s, const char *charset)
{
	const char	*pos;

	if ((s == NULL) || (charset == NULL))
		return (0);
	pos = s;
	while (*pos)
	{
		if (*pos == '\'' || *pos == '\"')
		{
			pos = ft_strchr(pos + 1, *pos);
			if (!pos)
				return (ft_strlen(s));
			pos++;
		}
		if (ft_strchr(charset, *pos))
			return (pos - s);
		else
			pos++;
	}
	return (pos - s);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	g_shell.shell_state = FOREGROUNG_JOB;
	g_shell.exit_code = 0;
	pid = fork();
	if (pid < 0)
	{
		printf("fork error: %s\n", strerror(errno));
		exit(1);
	}
	return (pid);
}

int	ft_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		printf("pipe error: %s\n", strerror(errno));
		exit(1);
	}
	return (0);
}

int	print_error(char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(msg);
	return (exit_code);
}
