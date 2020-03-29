# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/12 18:36:13 by cylemair          #+#    #+#              #
#    Updated: 2020/03/27 20:22:42 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc -g3

CFLAGS	+=	-Werror -Wall -Wextra

LDFLAGS	=	-I./includes/ -lft -lncurses -L ./libft/

INC		=	./includes/	\
			./libft/	\

INCLU	:=	$(addprefix -I, $(INC))

NAME	=	21sh

RM		=	rm -rf

SRC		=	srcs/main.c 		\
			srcs/vector.c		\
			srcs/getter.c		\
			srcs/string.c		\
			srcs/termi.c		\
			srcs/array.c		\
			srcs/exec.c			\
			srcs/tmp.c			\

OBJS	=	$(SRC:.c=.o)

all: $(NAME) $(SRC)

srcs/%.o: srcs/%.c
	@$(CC) $(INCLU) -c $< -o $@

$(NAME): $(OBJS) $(SRC)
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
