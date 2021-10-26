/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 00:52:50 by rkombu            #+#    #+#             */
/*   Updated: 2021/08/03 00:52:53 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infile(t_file *file)
{
	int		fd;

	fd = open(file->filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(file->filename, 1);
		if (g_shell.shell_state == FOREGROUNG_JOB)
			exit(1);
		else
			return (fd);
	}
	if (file->type == HERE_DOC)
		unlink(file->filename);
	return (fd);
}

int	create_outfile(t_file *file)
{
	int		fd;

	if (file->type == REGULAR)
		fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		print_error(file->filename, 1);
		if (g_shell.shell_state == FOREGROUNG_JOB)
			exit(1);
	}
	return (fd);
}
