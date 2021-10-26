/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 02:10:43 by rkombu            #+#    #+#             */
/*   Updated: 2021/09/15 02:10:48 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

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
	{
		free(file->filename);
		free(file);
		return (NULL);
	}
	name = ft_substr(start, 0, end - start);
	*p_end = end;
	file->filename = append_str(file->filename, name);
	free(name);
	return (file);
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
			break;
		*start = '\0';
		result = append_str(result, end);
		filename = extract_filename(start + 1, &end, c);
		if (!filename)
		{
			free(line);
			free(result);
			return (NULL);
		}
		ft_lstadd_back(files, ft_lstnew(filename));
	}
	result = append_str(result, end);
	free(line);
	return (result);
}

static char	*discard_redirections(char *line, t_cmd_line *cmd_line)
{
	line = process_redirects('<', line, &cmd_line->infiles);
	if (!line)
		return (NULL);
	line = process_redirects('>', line, &cmd_line->outfiles);
	return (line);
}

static void	init_cmd_lines(t_cmd_line *cmds, int n)
{
	while (n--)
	{
		cmds[n].argv = NULL;
		cmds[n].infiles = NULL;
		cmds[n].outfiles = NULL;
	}
}

t_parser	*parse_cmd_list(char *line)
{
	char *pipe;

	t_parser *parser = malloc(sizeof(t_parser));
	parser->num_cmd = 0;
	while (parser->num_cmd < MAXCMDS)
	{
		parser->cmd_list[parser->num_cmd++] = line;
		pipe = strchr_ignoring_quotes(line, '|');
		if (!pipe)
			break ;
		*pipe = '\0';
		line = pipe + 1;
		if (!*line)
		{
			free(parser);
			return (NULL);
		}
	}
	parser->cmd_list[parser->num_cmd] = NULL;
	parser->cmd_lines = malloc(sizeof(t_cmd_line) * parser->num_cmd);
	init_cmd_lines(parser->cmd_lines, parser->num_cmd);
	return (parser);
}

void	clear_file(void *ptr)
{
	t_file	*file;

	file = ptr;
	free(file->filename);
	if (file->type == HERE_DOC)
		free(file->delimiter);
	free(file);;
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

t_parser	*free_parser(t_parser *parser, bool error, int num)
{
	char	*token;
	int		i;

	if (error)
	{
		if (num < parser->num_cmd - 1)
			token = "|";
		else
			token = "newline";
		printf("minishell: syntax error near unexpected token `%s'\n", token);
	}
	i = 0;
	while (i < parser->num_cmd)
	{
		free_cmd_line(&parser->cmd_lines[i]);
		i++;
	}
	free(parser->cmd_lines);
	free(parser);
	return (NULL);
}

t_parser	*parse_input(char *line)
{
	t_parser	*parser;
	int			i;

	parser = parse_cmd_list(line);
	if (!parser) {
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	i = 0;
	while (i < parser->num_cmd)
	{
		if (!parse_cmd_line(parser->cmd_list[i], parser->cmd_lines + i))
			return (free_parser(parser, true, i));
		if (!parser->cmd_lines[i].argv[0]
			&& !parser->cmd_lines[i].infiles
			&& !parser->cmd_lines[i].outfiles)
			return (free_parser(parser, parser->num_cmd > 1, i));
		i++;
	}
	return (parser);
}
