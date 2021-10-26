/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 02:15:59 by rkombu            #+#    #+#             */
/*   Updated: 2021/09/15 02:16:06 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define MAXARGS			128		/* max args on a command line */
# define MAXCMDS			64		/* max simple commands piped together */

typedef enum e_file_type {REGULAR, APPEND, HERE_DOC}	t_file_type;

typedef struct s_file
{
	char		*filename;
	t_file_type	type;
	char		*delimiter;
}				t_file;

typedef struct s_cmd_line
{
	char		**argv;
	t_list		*outfiles;
	t_list		*infiles;
}				t_cmd_line;

typedef struct s_parser
{
	int			num_cmd;
	char		*cmd_list[MAXCMDS];
	t_cmd_line	*cmd_lines;
}				t_parser;

t_parser		*parse_input(char *line);
char			*strchr_ignoring_quotes(const char *s, int c);
unsigned int	strcspn_ignoring_quotes(const char *s, const char *charset);
t_parser		*parse_cmd_list(char *line);
bool			parse_cmd_line(char *line, t_cmd_line *cmd);
void			discard_quotes_in_argv(char **argv);
void			discard_quotes(char **str);
void			expand_vars(char **str, bool quotes);
void			expand_vars_in_redirect(char **str);
char			*get_var_name(char **str);
char			*expand(char *var);
char			**ft_split_ignoring_quotes(char const *s, char c);
t_cmd_line		*free_cmd_line(t_cmd_line *cmd_line);
t_parser		*free_parser(t_parser *parser, bool error, int i);
void			clear_file(void *ptr);
void			assign_heredoc_filename(t_parser *parser);
bool			read_here_docs(t_parser *parser);
void			expand_if(void *file);
void			handle_heredoc(t_file *file);
void			expand_here_doc(int fd_here_doc, char *delimeter);
bool			clean_here_docs(t_parser *parser);
void			delete_temp_file(void *file);

#endif
