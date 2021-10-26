/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:47:38 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/18 21:47:40 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_heredoc_filename(t_parser *parser)
{
	int		i;
	char	c;
	t_list	*lst;
	t_file	*file;
	char	filename[] = "heredoc_temp_a";


	i = 0;
	c = 'a';
	while (i < parser->num_cmd && c <= 'z')
	{
		lst = parser->cmd_lines[i].infiles;
		while (lst && c <= 'z')
		{
			file = lst->content;
			if (file->type == HERE_DOC)
			{
				file->delimiter = file->filename;
				filename[13] = c;
				file->filename = ft_strdup(filename);
				c++;
			}
			lst = lst->next;
		}
		i++;
	}
}

void	delete_temp_file(void *file)
{
	if (((t_file *)file)->type == HERE_DOC)
		unlink(((t_file *)file)->filename);
}

bool	clean_here_docs(t_parser *parser)
{
	int		i;

	g_shell.exit_code = 1;
	i = 0;
	while (i < parser->num_cmd)
	{
		ft_lstiter(parser->cmd_lines[i].infiles, delete_temp_file);
		i++;
	}
	free_parser(parser, false, 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (false);
}
