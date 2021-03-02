# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/12 18:36:13 by cylemair          #+#    #+#              #
#    Updated: 2021/03/02 18:47:32 by cylemair         ###   ########.fr        #
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

BUILTINS=	srcs/builtins/commands/change_directory.c	\
			srcs/builtins/commands/history.c			\
			srcs/builtins/commands/print_args.c			\
			srcs/builtins/commands/print_env.c			\
			srcs/builtins/commands/set_env.c			\
			srcs/builtins/commands/unset_env.c			\
			srcs/builtins/env_key_exists.c				\
			srcs/builtins/free_builtin.c				\
			srcs/builtins/init_builtin.c				\
			srcs/builtins/select_builtin.c 				\

EXEC	=	srcs/execution/handle_commands.c					\
			srcs/execution/handle_execution.c					\
			srcs/execution/execute_command/choose_command_path.c\
			srcs/execution/execute_command/execute_command.c	\
			srcs/execution/pipe/handle_heredoc.c				\
			srcs/execution/pipe/handle_pipe.c					\
			srcs/execution/pipe/pipe_fork.c						\
			srcs/execution/pipe/set_stdin_pipe_redirection.c	\
			srcs/execution/pipe/write_heredoc.c					\
			srcs/execution/redirections/execute_redirections.c	\
			srcs/execution/redirections/restore_redirections.c	\

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
			srcs/parsing/redirections_parsing.c		\
			srcs/parsing/redirections_setup.c		\
			srcs/parsing/redirections_tools.c		\
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
			srcs/other/get_env_var_value.c			\
			srcs/other/main.c 						\
			srcs/other/print_error.c				\
			srcs/other/redirections_struct.c		\
			srcs/other/signals.c					\
			srcs/other/tmp.c						\

SRCS	=	$(BUILTINS)	\
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
