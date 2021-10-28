# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurky <emurky@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/26 02:41:42 by rkombu            #+#    #+#              #
#    Updated: 2021/10/28 19:45:27 by emurky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCSDIR			= ./src

SRCS			= $(addprefix $(SRCSDIR)/, \
				util.c parser.c parse_command.c ft_split_ignoring_quotes.c \
				env_var.c minishell.c eval.c signal.c here_doc.c command.c \
				quotes.c manage_files.c path.c here_doc_util.c var.c \
				quotes_util.c builtins.c)

SRCS			+= $(addprefix $(SRCSDIR)/builtins/, \
				mini_cd.c mini_pwd.c mini_echo.c mini_export.c mini_env.c \
				mini_unset.c mini_exit.c)

OBJS			= $(SRCS:.c=.o)
DEPS			= $(SRCS:.c=.d)

NAME			= minishell

CC 				= gcc
RM 				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address #-o3

CPPFLAGS		=	-MMD -I./include -I./libft \
					-I/usr/local/Cellar/readline/8.1.1/include

LIBS			=	-L./libft -lft \
					-L/usr/local/Cellar/readline/8.1.1/lib -lreadline

all:			$(NAME)

$(NAME):		$(OBJS) Makefile
				$(MAKE) -C ./libft -j 4
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus:			all

-include		$(DEPS)

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS) $(DEPS)

fclean:			clean
				$(RM) ./libft/libft.a
				$(RM) $(NAME) $(NAME).dSYM

re:				fclean all


sc:
				rm -rf *.o *.a */*.o */*.a */*.d *.d 'minishell '* minishell

.PHONY:			all clean fclean re bonus
