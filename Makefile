# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/12 18:36:13 by cylemair          #+#    #+#              #
#    Updated: 2021/03/01 19:58:30 by cylemair         ###   ########.fr        #
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

ENV		=	srcs/env/built_in.c						\
			srcs/env/change_directory.c				\
			srcs/env/env.c							\

EXEC	=	srcs/exec/execution.c					\
			srcs/exec/heredoc_execution.c			\
			srcs/exec/pipe.c						\
			srcs/exec/redirections_execution.c		\
			srcs/exec/redirections_parsing.c		\
			srcs/exec/redirections_setup.c			\
			srcs/exec/redirections_struct.c			\
			srcs/exec/redirections_tools.c			\
			srcs/exec/syscall_execution.c			\

PARSE	=	srcs/parsing/args_creation.c			\
			srcs/parsing/args.c						\
			srcs/parsing/array.c					\
			srcs/parsing/create_non_quoted_arg.c	\
			srcs/parsing/create_quoted_arg.c		\
			srcs/parsing/end_of_line.c				\
			srcs/parsing/get_var.c					\
			srcs/parsing/handle_new_entry.c			\
			srcs/parsing/line_content_to_args.c		\
			srcs/parsing/parse_array.c				\
			srcs/parsing/parse_word.c				\
			srcs/parsing/split_all_whitespace.c		\
			srcs/parsing/string.c					\
			srcs/parsing/unquote.c					\
			srcs/parsing/vector.c					\

HEREDOC	=	srcs/heredoc/heredoc.c					\
			srcs/heredoc/format_heredoc.c			\
			srcs/heredoc/heredoc_array.c			\
			srcs/heredoc/update_heredoc.c			\

TERM	=	srcs/terminal/arrow_left_right.c		\
			srcs/terminal/arrow_up_down.c			\
			srcs/terminal/conf_term.c				\
			srcs/terminal/ctrl_key_vertical.c		\
			srcs/terminal/ctrl_key.c				\
			srcs/terminal/cursors_set.c				\
			srcs/terminal/cursors.c					\
			srcs/terminal/key.c						\
			srcs/terminal/select.c					\
			srcs/terminal/termcaps.c				\
			srcs/terminal/termi.c					\

OTHER	=	srcs/other/boolean_tools.c				\
			srcs/other/boolean_tools2.c				\
			srcs/other/history.c					\
			srcs/other/main.c 						\
			srcs/other/print_error.c				\
			srcs/other/signals.c					\
			srcs/other/tmp.c						\

SRCS	=	$(ENV)		\
			$(EXEC)		\
			$(PARSE)	\
			$(HEREDOC)	\
			$(TERM)		\
			$(OTHER)	\

OBJS	=	$(SRCS:.c=.o)

all: $(NAME) $(SRCS) $(HEADERS)

srcs/%.o: srcs/%.c $(HEADERS)
	@$(CC) $(INCLU) -c $< -o $@

$(NAME): $(OBJS) $(SRCS) $(HEADERS)
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
