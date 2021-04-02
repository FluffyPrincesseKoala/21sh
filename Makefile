# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/12 18:36:13 by cylemair          #+#    #+#              #
#    Updated: 2021/04/01 21:56:43 by cylemair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang

CFLAGS	+=	-Werror -Wall -Wextra

LDFLAGS	=	-I./includes/ -lft -lncurses -L ./libft/

INC		=	./includes/	\
			./libft/	\

INCLU	:=	$(addprefix -I, $(INC))

INCPATH	=	./includes/

HEADER	=	vingt_et_un_sh.h

HEADERS	=	$(addprefix $(INCPATH), $(HEADER))

NAME	=	21sh

RM		=	rm -rf

BUILTINS=	srcs/builtins/commands/change_directory.c						\
			srcs/builtins/commands/history.c								\
			srcs/builtins/commands/print_args.c								\
			srcs/builtins/commands/print_env.c								\
			srcs/builtins/commands/set_env.c								\
			srcs/builtins/commands/unset_env.c								\
			srcs/builtins/utils/change_value_in_array.c						\
			srcs/builtins/utils/env_key_exists.c							\

EXEC	=	srcs/execution/handle_commands.c								\
			srcs/execution/handle_execution.c								\
			srcs/execution/execute_command/choose_command_path.c			\
			srcs/execution/execute_command/execute_command.c				\
			srcs/execution/pipe/handle_heredoc.c							\
			srcs/execution/pipe/handle_pipe.c								\
			srcs/execution/pipe/pipe_fork.c									\
			srcs/execution/pipe/set_stdin_pipe_redirection.c				\
			srcs/execution/pipe/write_heredoc.c								\
			srcs/execution/redirections/execute_redirections.c				\
			srcs/execution/redirections/restore_redirections.c				\

PARSE	=	srcs/parsing/end_of_line.c										\
			srcs/parsing/format_line.c										\
			srcs/parsing/handle_parsing_execution.c							\
			srcs/parsing/line_content_to_args.c								\
			srcs/parsing/args/add_arg.c										\
			srcs/parsing/args/create_arg.c									\
			srcs/parsing/args/create_quoted_arg.c							\
			srcs/parsing/args/create_non_quoted_arg.c						\
			srcs/parsing/args/del_one_arg.c									\
			srcs/parsing/args/detach_arg.c									\
			srcs/parsing/args/free_all_args.c								\
			srcs/parsing/args/insert_new_arg.c								\
			srcs/parsing/args/is_non_escaped_quote.c						\
			srcs/parsing/args/parse_var.c									\
			srcs/parsing/heredoc/fill_heredoc_array.c						\
			srcs/parsing/heredoc/heredoc.c									\
			srcs/parsing/heredoc/is_eof.c									\
			srcs/parsing/heredoc/is_heredoc_end.c							\
			srcs/parsing/heredoc/set_heredoc.c								\
			srcs/parsing/heredoc/update_heredoc.c							\
			srcs/parsing/heredoc/concat_args_in_heredoc.c					\
			srcs/parsing/heredoc/format_heredoc.c							\
			srcs/parsing/redirections/init_redirections_setup_functions.c	\
			srcs/parsing/redirections/is_stdout_and_stderr_redirection.c	\
			srcs/parsing/redirections/search_file_word.c					\
			srcs/parsing/redirections/search_left_fd.c						\
			srcs/parsing/redirections/search_right_fd.c						\
			srcs/parsing/redirections/setup_command_redirections.c			\
			srcs/parsing/utils/add_value_to_array.c							\
			srcs/parsing/utils/free_array.c									\
			srcs/parsing/utils/free_vector.c								\
			srcs/parsing/utils/is_separator.c								\
			srcs/parsing/utils/pending_line.c								\
			srcs/parsing/utils/push_entry.c									\
			srcs/parsing/utils/use_shell_var.c								\

TERM	=	srcs/terminal/init_key_functions.c								\
			srcs/terminal/termi.c											\
			srcs/terminal/arrows/arrow_down.c								\
			srcs/terminal/arrows/arrow_left.c								\
			srcs/terminal/arrows/arrow_right.c								\
			srcs/terminal/arrows/arrow_up.c									\
			srcs/terminal/arrows/get_y_cursor.c								\
			srcs/terminal/arrows/clear_term.c								\
			srcs/terminal/ctrl_keys/clean_screen.c							\
			srcs/terminal/ctrl_keys/ctrl_down.c								\
			srcs/terminal/ctrl_keys/ctrl_left.c								\
			srcs/terminal/ctrl_keys/ctrl_right.c							\
			srcs/terminal/ctrl_keys/ctrl_up.c								\
			srcs/terminal/ctrl_keys/init_xy.c								\
			srcs/terminal/ctrl_keys/return_exit.c							\
			srcs/terminal/selections/select_back.c							\
			srcs/terminal/selections/select_copy.c							\
			srcs/terminal/selections/select_next.c							\
			srcs/terminal/selections/select_paste.c							\
			srcs/terminal/simple_keys/delchar.c								\
			srcs/terminal/simple_keys/key_back.c							\
			srcs/terminal/simple_keys/key_last.c							\
			srcs/terminal/simple_keys/key_start.c							\
			srcs/terminal/simple_keys/key_suppr.c							\
			srcs/terminal/utils/clear.c										\
			srcs/terminal/utils/clear_cursor_struct.c						\
			srcs/terminal/utils/conf_term.c									\
			srcs/terminal/utils/find_cursor_node.c							\
			srcs/terminal/utils/get_win_max_col.c							\
			srcs/terminal/utils/move_left.c									\
			srcs/terminal/utils/move_right.c								\
			srcs/terminal/utils/print_rest.c								\
			srcs/terminal/utils/set_cursors.c								\
			srcs/terminal/utils/uncolor.c									\
			srcs/terminal/utils/unselect.c									\
			srcs/terminal/utils/term_put.c									\

UTILS	=	srcs/free_bash.c												\
			srcs/init_bash.c												\
			srcs/main.c 													\
			srcs/loop.c														\
			srcs/setup_signals.c											\
			srcs/utils/booleans/command_is_piped.c							\
			srcs/utils/booleans/is_child.c									\
			srcs/utils/booleans/is_quote.c									\
			srcs/utils/errors/check_failed_fork.c							\
			srcs/utils/errors/error_code_to_message.c						\
			srcs/utils/errors/print_failed_fork_error.c						\
			srcs/utils/errors/put_error_msg.c								\
			srcs/utils/free_redirections.c									\
			srcs/utils/get_env_var_value.c									\
			srcs/utils/new_redirection.c									\
			srcs/utils/pchar.c												\
			srcs/utils/prompt.c												\
			srcs/utils/pull_line.c											\
			srcs/utils/vect_new.c											\

SRCS	=	$(BUILTINS)														\
			$(EXEC)															\
			$(PARSE)														\
			$(TERM)															\
			$(UTILS)														\
			

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
