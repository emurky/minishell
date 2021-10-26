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
	char		*pipe;
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
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
	if (!parser)
	{
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
