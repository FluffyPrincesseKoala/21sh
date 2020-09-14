# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/12 18:36:13 by cylemair          #+#    #+#              #
#    Updated: 2020/06/12 18:06:17 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc -g3

CFLAGS	+=	-Werror -Wall -Wextra

LDFLAGS	=	-I./includes/ -lft -lncurses -L ./libft/

INC		=	./includes/	\
			./libft/	\

INCLU	:=	$(addprefix -I, $(INC))

INCPATH	=	./includes/

HEADER	=	21sh.h

HEADERS	=	$(addprefix $(INCPATH), $(HEADER))

NAME	=	21sh

RM		=	rm -rf

SRC		=	srcs/main.c 			\
			srcs/vector.c			\
			srcs/getter.c			\
			srcs/string.c			\
			srcs/termi.c			\
			srcs/array.c			\
			srcs/exec.c				\
			srcs/tmp.c				\
			srcs/replace_substr.c	\
			srcs/arrow.c			\
			srcs/key.c				\
			srcs/lst.c				\
			srcs/convert.c			\
			srcs/separator.c		\
			srcs/get_var.c			\
			srcs/end_of_line.c		\
			srcs/cursor.c			\
			srcs/select.c			\

OBJS	=	$(SRC:.c=.o)

all: $(NAME) $(SRC) $(HEADERS)

srcs/%.o: srcs/%.c $(HEADERS)
	@$(CC) $(INCLU) -c $< -o $@

$(NAME): $(OBJS) $(SRC) $(HEADERS)
	@make -C libft/
	@printf '\033[38;5;29m building: \033[38;5;50m $(NAME) \033[0m\n'
	@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	@make clean -C libft/
	@printf '\033[38;5;29m delete: \033[1;31m $(OBJS) \033[0m\n'
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C libft/
	@$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re
