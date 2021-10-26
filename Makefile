# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkombu <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/26 02:41:42 by rkombu            #+#    #+#              #
#    Updated: 2021/04/26 02:41:48 by rkombu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCSDIR			= ./src

SRCS			= $(addprefix $(SRCSDIR)/, \
				util.c parser.c parse_command.c ft_split_ignoring_quotes.c \
				env_var.c minishell.c eval.c signal.c here_doc.c command.c \
				quotes.c manage_files.c path.c here_doc_util.c var.c \
				quotes_util.c builtins.c)

SRCS			+= $(addprefix ./src/builtins/, \
				mini_cd.c mini_pwd.c mini_echo.c mini_export.c mini_env.c \
				mini_unset.c mini_exit.c)

OBJS			= $(SRCS:.c=.o)

NAME			= minishell

CC 				= gcc

RM 				= rm -rf

CFLAGS			= -Wall -Wextra -Werror -I./include \
				-I/usr/local/Cellar/readline/8.1/include -g -fsanitize=address #-o3

LIBS			= -L./libft -lft -L/usr/local/Cellar/readline/8.1/lib -lreadline

all:			$(NAME)

$(NAME):		$(OBJS)
				$(MAKE) -C ./libft -j 4
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus:			all

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)

fclean:			clean
				$(RM) ./libft/libft.a
				$(RM) $(NAME) $(NAME).dSYM

re:				fclean all


.PHONY:			all clean fclean re
