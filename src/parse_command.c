/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:45:39 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/26 20:45:42 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file	*extract_filename(char *start, char **p_end, char c)
{
	t_file	*file;
	char	*end;
	char	*name;

	file = malloc(sizeof(t_file));
	file->filename = ft_strdup("");
	file->type = REGULAR;
	file->delimiter = NULL;
	if (start[0] == c)
	{
		file->type = 1 + (c == '<');
		start++;
	}
	while (*start == ' ')
		start++;
	end = start + strcspn_ignoring_quotes(start, " <>");
	if (start == end)
		return (ft_free_and_return(file->filename, file, NULL));
	name = ft_substr(start, 0, end - start);
	*p_end = end;
	file->filename = append_str(file->filename, name);
	return (ft_free_and_return(name, NULL, file));
}

static char	*process_redirects(char c, char *line, t_list **files)
{
	char	*result;
	char	*start;
	char	*end;
	t_file	*filename;

	result = ft_strdup("");
	end = line;
	while (true)
	{
		start = strchr_ignoring_quotes(end, c);
		if (!start)
			break ;
		*start = '\0';
		result = append_str(result, end);
		filename = extract_filename(start + 1, &end, c);
		if (!filename)
			return (ft_free_and_return(line, result, NULL));
		ft_lstadd_back(files, ft_lstnew(filename));
	}
	result = append_str(result, end);
	return (ft_free_and_return(line, NULL, result));
}

char	*discard_redirections(char *line, t_cmd_line *cmd_line)
{
	line = process_redirects('<', line, &cmd_line->infiles);
	if (!line)
		return (NULL);
	line = process_redirects('>', line, &cmd_line->outfiles);
	return (line);
}

bool	parse_cmd_line(char *line, t_cmd_line *cmd)
{
	line = discard_redirections(ft_strdup(line), cmd);
	if (!line)
		return (free_cmd_line(cmd));
	expand_vars(&line, true);
	cmd->argv = ft_split_ignoring_quotes(line, ' ');
	free(line);
	return (cmd);
}

t_cmd_line	*free_cmd_line(t_cmd_line *cmd)
{
	int	i;

	ft_lstclear(&cmd->infiles, clear_file);
	ft_lstclear(&cmd->outfiles, clear_file);
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	return (NULL);
}
