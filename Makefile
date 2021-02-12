# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/12 18:36:13 by cylemair          #+#    #+#              #
#    Updated: 2021/02/12 19:26:52 by cylemair         ###   ########.fr        #
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

SRC		=	srcs/args.c						\
			srcs/array.c					\
			srcs/arrow_left_right.c			\
			srcs/arrow_up_down.c			\
			srcs/boolean_tools.c			\
			srcs/boolean_tools2.c			\
			srcs/built_in.c					\
			srcs/change_directory.c			\
			srcs/conf_term.c				\
			srcs/create_args.c				\
			srcs/ctrl_key.c					\
			srcs/ctrl_key_vertical.c		\
			srcs/cursor.c					\
			srcs/end_of_line.c				\
			srcs/env.c						\
			srcs/execution.c				\
			srcs/key.c						\
			srcs/get_var.c					\
			srcs/getter.c					\
			srcs/handle_quotes.c			\
			srcs/handle_separator.c			\
			srcs/heredoc.c					\
			srcs/heredoc_execution.c		\
			srcs/history.c					\
			srcs/main.c 					\
			srcs/parse_array.c				\
			srcs/parse_word.c				\
			srcs/pipe.c						\
			srcs/print_error.c				\
			srcs/replace_substr.c			\
			srcs/redirections_execution.c	\
			srcs/redirections_parsing.c		\
			srcs/redirections_setup.c		\
			srcs/redirections_struct.c		\
			srcs/redirections_tools.c		\
			srcs/select.c					\
			srcs/signals.c					\
			srcs/split_all_whitespace.c		\
			srcs/string.c					\
			srcs/syscall_execution.c		\
			srcs/termcaps.c					\
			srcs/termi.c					\
			srcs/tmp.c						\
			srcs/vector.c

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
