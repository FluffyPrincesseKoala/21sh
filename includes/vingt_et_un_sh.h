/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingt_et_un_sh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:27:32 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/10 12:52:27 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGT_ET_UN_SH_H
# define VINGT_ET_UN_SH_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdio.h>

# include <term.h>

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "structs.h"

# define BACK_BLUE			"\033[46m"
# define BLUE				"\033[38;5;61m"
# define GREEN				"\033[38;5;29m"
# define CYAN				"\033[38;5;50m"
# define RED 	    		"\033[1;31m"
# define RESET		    	"\033[0m"
# define NODIR	    		"Not a directory\n"
# define DENY		    	"Permission denied\n"
# define UNOW		    	": Command not found\n"
# define SYNTAX         	"21sh: syntax error near unexpected symbol "
# define NOFOD				"No such file or directory\n"
# define HOOK_MALLOC		"Malloc return NULL value"
# define E_TERM_SET			"TERM must be set (see 'env')"
# define E_TERM_CAP			"Could not access to the termcap database"
# define E_TERM_DEF			"Terminal type is not defined in termcap db"
# define E_CHDIR	    	-1
# define UP					"up"
# define DOWN				"do"
# define LEFT				"le"
# define RIGHT				"nd"
# define SAVE				"sc"
# define RESET_C			"rc"
# define SNTX_ERR         	42
# define TRUE				1
# define FALSE				0
# define SUCCESS			1
# define FAIL				0
# define EXIT				-1
# define NOQUOTE			0
# define MAX_KEY			18
# define MAX_TERMCAPS		8
# define NB_BUILTIN			6
# define MAX_INPUT_SIZE		7
# define CHECK_PREV_ARGS	1

# define SIMPLE_OUTPUT_REDIRECTION ">"
# define APPEND_OUTPUT_REDIRECTION ">>"
# define INPUT_REDIRECTION "<"
# define CLOSE_DIRECTION '-'

/*
** APPENDING_OUTPUT_FLAGS = SIMPLE_OUTPUT_FLAGS | O_APPEND
** INPUT_FLAGS = O_RDONLY
** NEW_FILE_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
** SIMPLE_OUTPUT_FLAGS = O_WRONLY | O_CREAT
*/
# define APPENDING_OUTPUT_FLAGS 1089
# define INPUT_FLAGS 0
# define NEW_FILE_MODE 436
# define SIMPLE_OUTPUT_FLAGS 65

# define STDOUT 1
# define STDERR 2
# define STDIN 0
# define STDOUT_AND_STDERR -1
# define CLOSE_FD -1
# define AMBIGUOUS -2
# define NO_LEFT_FD -2
# define NO_RIGHT_FD 0

# define MALLOC_ERROR 1
# define AMBIGUOUS_REDIRECTION_ERROR 2
# define UNEXPECT_COMMAND_END_ERROR 3
# define OPEN_ERROR 4
# define NO_APPENDING_IN_FILE_DIRECTOR_ERROR 5
# define ENV_FAIL 6

struct termios	old_term;
struct termios	new_term;
t_bash			*g_data;

void			*free_bash(t_bash *data);
t_bash			*init_bash(char **env);
void			loop(t_bash *data);
void			setup_signals(void);

/*
** ===========
**	BUILT-INS
** ===========
*/

/*
** Commands
*/
void			change_directory(t_bash *data, t_vect *command);
void			history(t_bash *data, t_vect *cmd);
void			print_args(t_bash *data, t_vect *command);
void			print_env(t_bash *data, t_vect *cmd);
void			print_history(t_bash *data);
void			set_env(t_bash *data, t_vect *command);
void			unset_env(t_bash *data, t_vect *command);

/*
** Utils
*/
char			**change_value_in_array(char **src, char *key, char *value);
int				env_key_exists(char **env, char *key);

/*
** ===========
**  EXECUTION
** ===========
*/

int				handle_commands(t_bash *data, t_vect *command);
int				handle_execution(t_bash *data, t_vect *command);

/*
** Execute Command
*/
char			*choose_command_path(t_bash *data, char *command_name);
void			execute_command(t_bash *data, t_vect *command);

/*
** Pipe
*/
void			handle_heredoc(t_bash *data, t_vect *command);
int				handle_pipe(t_bash *data, t_vect *command);
void			pipe_fork(t_bash *data, t_vect *command,
	int pipe_fd[2], int heredoc);
void			set_stdin_pipe_redirection(t_bash *data, t_vect *command,
	int pipe_fd[2]);
void			write_heredoc(t_bash *data, t_vect *command, int pipe_fd[2]);

/*
** Redirections
*/
int				execute_redirections(t_bash *data, t_vect *command,
	t_redirection *redirection);
void			restore_directions(t_redirection *redirection);

/*
** =========
**  PARSING
** =========
*/

int				end_of_line(t_bash **data);
void			format_line(t_bash *data);
int				handle_parsing_execution(t_bash *data);
void			line_content_to_args(t_bash *data, char *line);

/*
** Args
*/
void			add_arg(t_arg **head, t_arg *new_arg);
t_arg			*create_arg(char *content, char *quoted_string);
size_t			create_non_quoted_arg(t_bash *data, t_vect *cmd,
	char *line_extract);
size_t			create_quoted_arg(t_bash *data, t_vect *cmd,
	char *line_substr, char quote);
void			del_one_arg(t_arg *arg, t_vect *cmd);
void			detach_arg(t_arg *arg, t_vect *cmd);
void			free_all_args(t_arg **arg, int flag);
int				insert_new_arg(t_vect *command, t_arg *previous, char *s);
int				is_non_escaped_quote(const char *s, char quote, int i);
void			parse_var(t_arg *head, char **env);

/*
** Heredoc
*/
void			fill_heredoc_array(t_bash *data, t_vect *cmd, char **line);
void			heredoc(t_bash *data);
int				is_eof(t_vect *cmd);
int				is_heredoc_end(t_bash *data, char *line, t_vect *vector);
t_arg			*set_heredoc(t_bash *data, t_vect **cmd);
void			update_heredoc(t_bash *data);
char			*concat_args_in_heredoc(t_arg *arg);

/*
** Redirections
*/
int				init_redirections_setup_functions(t_bash *data);
int				is_stdout_and_stderr_redirection(int left_fd, int right_fd);
char			*search_file_word(t_vect *cmd, t_arg *arg,
	int substring_index, int *error);
int				search_left_fd(t_vect *cmd, t_arg *arg, int def, int *error);
int				search_right_fd(t_vect *cmd, t_arg *arg,
	char *substring, int *error);
int				setup_command_redirections(t_bash *data, t_vect *cmd);

/*
** Utils
*/
char			**add_value_to_array(char **src, char *value);
void			free_array(char **array);
void			free_vector(t_vect **head, int flag);
char			is_separator(char c);
int				pending_line(char *str);
void			push_entry(t_bash *data, char *entry, char **line, int pos);
char			*use_shell_var(char **env, char *str);

/*
** ==========
**  TERMINAL
** ==========
*/

void			init_key_functions(t_key **fct);
void			termi(t_bash *data, char *buff);

/*
** Arrows
*/
void			arrow_down(t_bash *data);
void			arrow_left(t_bash *data);
void			arrow_right(t_bash *data);
void			arrow_up(t_bash *data);
void			clear_term(char *str);
int				get_y_cursor(t_term *src);

/*
** Ctrl Keys
*/
void			clean_screen(t_bash *data);
void			ctrl_down(t_bash *data);
void			ctrl_left(t_bash *data);
void			ctrl_right(t_bash *data);
void			ctrl_up(t_bash *data);
void			init_xy(t_bash *data, int *x, int *y, int max);
void			return_exit(t_bash *data);

/*
** Selections
*/
void			select_back(t_bash *data);
void			select_next(t_bash *data);
void			select_copy(t_bash *data);
void			select_paste(t_bash *data);

/*
** Simple Keys
*/
char			*delchar(char *ref, int pos);
void			key_last(t_bash *data);
void			key_start(t_bash *data);
void			key_back(t_bash *data);
void			key_suppr(t_bash *data);

/*
** Utils
*/
void			clear(void);
void			clear_cursor_struct(t_term **cursor);
int				conf_term();
t_term			*find_cursor_node(t_term **head, int idx,
	int idx_max, int plen);
int				get_win_max_col();
void			move_left(t_bash *data);
void			move_right(t_bash *data);
int				print_rest(char *str, int pos, char *old);
void			set_cursors(t_bash *data, t_term **cursor, char *str, int max);
void			term_put(char *esc);
void			uncolor(t_bash *data);
void			unconf_term();
void			unselect(t_bash *data);

/*
** =======
**  UTILS
** =======
*/

void			free_redirections(t_vect *command);
char			*get_env_var_value(char **env, char *name);
t_redirection	*new_redirection(t_vect *cmd);
int				pchar(int c);
int				prompt(char **env, int short_prompt);
void			pull_line(t_vect **head);
t_vect			*vect_new(t_arg *args, char *line);

/*
** Booleans
*/
int				command_is_piped(t_vect *command);
int				fork_failed(pid_t pid);
int				is_child(pid_t pid);
int				is_quote(char c);

/*
** Errors
*/
void			error_code_to_message(int *error);
void			print_failed_fork_error(pid_t pid);
void			put_error_msg(char *error);

/*
** ===================
**	DEBUG & UNIT_TEST
** ===================
*/

void			currsor_info(t_term *curr, int count);
void			hello();
void			info(char *str);

#endif
