# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkombu <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 23:43:44 by rkombu            #+#    #+#              #
#    Updated: 2020/11/09 23:43:48 by rkombu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES			= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
			ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
			ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
			ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
			ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_error.c ft_str_truncate.c

B_SOURCES		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_free_and_return.c

OBJECTS			= $(SOURCES:.c=.o)

B_OBJECTS		= $(B_SOURCES:.c=.o)

NAME			= libft.a

CC			= gcc

RM 			= rm -f

ARFLAGS			= rcs

LIB			= ar $(ARFLAGS)

CFLAGS			= -Wall -Wextra -Werror

all::			$(NAME)

$(NAME):		$(OBJECTS) $(B_OBJECTS)
				$(LIB) $(NAME) $(OBJECTS) $(B_OBJECTS)

bonus:			all


clean:
				$(RM) $(OBJECTS) $(B_OBJECTS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re




