# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 15:09:42 by cylemair          #+#    #+#              #
#    Updated: 2020/03/12 17:50:02 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang -g3

CFLAGS	+=	-Werror -Wall -Wextra

LDFLAGS	=	-I./includes/ -lft -L ./libft/

INC		=	./includes/	\
			./libft/	\

INCLU	:=	$(addprefix -I, $(INC))

NAME	=	minishell

RM		=	rm -rf

SRC		=	srcs/main.c 		\
			srcs/copy_env.c		\
			srcs/exec.c			\
			srcs/std_parse.c	\
			srcs/cd.c			\
			srcs/builtin.c		\
			srcs/usefull.c		\
			srcs/vector.c		\
			srcs/env_key.c		\
			srcs/count.c		\
			srcs/count_bis.c	\
			srcs/get_var.c		\
			srcs/tilt.c			\

OBJS	=	$(SRC:.c=.o)

all: $(NAME)

srcs/%.o: srcs/%.c
	@$(CC) $(INCLU) -c $< -o $@

$(NAME): $(OBJS)
	@make -C libft/
	@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	@make clean -C libft/
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C libft/
	@$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re
