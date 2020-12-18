/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:37:19 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/01 21:00:11 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINETUNSH_H_
# define VINETUNSH_H_

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

#include <term.h>

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
# define CONTENT            arg->content
# define IDX		   		data->iterator
# define LINE		   		data->vector->line
# define VECT		   		data->vector
# define VECT_UP	   		data->vector->up
# define VECT_DOWN	   		data->vector->down
# define REDIRECTION_SETUP  data->redirections_setup
# define CUR_X				(data->iterator + data->prompt_len) % w.ws_col
# define CUR_Y		    	(data->iterator + data->prompt_len) / w.ws_col
# define LEN_Y				(ft_strlen(LINE) + data->prompt_len) / w.ws_col
# define ONLY_WCHAR			(count_delim(LINE, ' ') != ft_strlen(LINE))
# define UP					tputs(tgoto(tgetstr("up", NULL), 0 , 0), 1, &pchar)
# define CDOWN				tputs(tgoto(tgetstr("do", NULL), 0 , 0), 1, &pchar)
# define LEFT				tputs(tgoto(tgetstr("le", NULL), 0 , 0), 1, &pchar)
# define RIGHT				tputs(tgoto(tgetstr("nd", NULL), 0 , 0), 1, &pchar)
# define SAVE_C				tputs(tgoto(tgetstr("sc", NULL), 0 , 0), 1, &pchar)
# define RESET_C			tputs(tgoto(tgetstr("rc", NULL), 0 , 0), 1, &pchar)
# define CLEAR				tputs(tgetstr("cl", NULL), 1, &pchar)
# define GOTO(X,Y)			tputs(tgoto(tgetstr("cm", NULL), X, Y), 1, &pchar)
# define TRUE				1
# define FALSE				0
# define NOQUOTE			0
# define MAX_KEY			16


# define SIMPLE_OUTPUT_REDIRECTION ">"
# define APPENDING_OUTPUT_REDIRECTION ">>"
# define INPUT_REDIRECTION "<"
# define CLOSE_DIRECTION '-'

# define NEW_FILE_MODE	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
# define SIMPLE_OUTPUT_FLAGS O_WRONLY | O_CREAT
# define APPENDING_OUTPUT_FLAGS SIMPLE_OUTPUT_FLAGS | O_APPEND
# define INPUT_FLAGS O_RDONLY

# define STDOUT 1
# define STDERR 2
# define STDIN 0
# define STDOUT_AND_STDERR -1
# define CLOSE_FD -1
# define AMBIGUOUS -2
# define NO_RIGHT_FD 0

# define MALLOC_ERROR 1
# define AMBIGUOUS_REDIRECTION_ERROR 2
# define UNEXPECT_COMMAND_END_ERROR 3
# define OPEN_ERROR 4

struct termios	old_term;
struct termios	new_term;

/*
**	t_vect manipulation (keep current and old entry)
*/

t_vect		*vect_new(t_arg *args, char *line);
t_vect		*vect_add(t_vect **head, t_vect *new);
t_vect		*vect_push(t_vect **head, t_vect *new);
size_t		count_arg(t_vect *head);
t_vect		*link_history(t_vect **head, t_vect *new);
void		pull_line(t_vect **head);
void		free_vector(t_vect **head);

/*
**	ARRAY FORMATING
*/

void		free_array(char **array);
char		**copy_array(char **array);
int			array_len(char **array);
int			array_total_len(char **array);
void		print_array(char **array);
char		**array_add_value(char **src, char *value);
char		**change_array_value(char **src, char *key, char *value);

/*
**	STDIN & TERM RELATED
*/

int			init_term();
int			conf_term();
void		unconf_term();
int			handle_new_entry(t_bash *data, char *entry, int pos);

void		arrow_key(t_bash *data, char *buff);

void		key_last(t_bash *data);
void		key_start(t_bash *data);
void		key_back(t_bash *data);
void		key_suppr(t_bash *data);

void		ctrl_right(t_bash *data);
void		ctrl_left(t_bash *data);
void		ctrl_down(t_bash *data);
void		ctrl_up(t_bash *data);

void		arrow_left(t_bash *data);
void		arrow_right(t_bash *data);
void		arrow_down(t_bash *data);
void		arrow_up(t_bash *data);

void		move_left(t_bash *data);
void		move_right(t_bash *data);

/*
**	STRING FORMATING
*/
void		detach_arg(t_arg *arg, t_vect *cmd);
size_t		args_len(t_arg *arg);
char		*addchar(char *str, char c, int pos);
char		*replace_delim(char *str, char delim, char new);
int			pstr(char const *str);
int			pchar(int c);
size_t		count_delim(char *str, int delim);
char		*replace_delim(char *str, char delim, char new);
char		*replace_substr(char *str, char *old, char *new);
char		*merge_string_from_array(char **src, int size, int start);
void		push_entry(t_bash *data, char *entry, char **line, int pos);

/*
**	OTHER STUFF
*/

void		hello();
int			prompt(char **env, int short_prompt);
void		loop(t_bash *data);
char		*build_path(char **env, t_vect *lst);
void		handle_fork(t_bash *data, t_vect *cmd);
int			print_rest(char *str, int pos, char *old);
void		puterror(int error);
int			fork_failed(pid_t pid);
int			is_child(pid_t pid);
void 		set_up_signals();
void		clear_term(char *str);
void		put_error_msg(char *error);
void		*free_bash(t_bash *data);

/*
**	PARSING
*/

//t_vect		*new_arg(t_arg *args, t_vect *new);
int			next_delim(char **array, int start);
void		read_separator(char **table, t_bash *data);
void		format_line(t_bash *data);
void		get_var(t_arg **head, char **env);
void		get_tilt(t_arg **head, char **env);
int			len_between_last_delim(char *str, char delim, int start);
int			get_curent_line(char *str, int pos, int max, int prompt);
int			lendelim(char *str, char delim, int start);
size_t		count_delim(char *str, int delim);
int   		handle_eol(t_bash *data, char *buff);
int			pending_line(char *str);
char		*del_all_delim_in(char *str, char delim);
void		words_as_args(char **table, t_bash *data);

/*
**	LIST STUFF
*/

void		free_all_vectors(t_vect *vect);

/*
** ARGS
*/

t_arg   	*new_arg(char *content, char quote);
t_arg  		*add_arg(t_arg **head, t_arg *new);
int    		insert_new_arg(t_arg *previous, char *s);
char    	**arg_to_array(t_bash *data, t_arg *arg);
void		del_one_arg(t_arg *arg, t_vect *cmd);
void    	free_all_args(t_arg *arg);

/*
**	CURSOR TERM STRUCT
*/

void		charadd_to_term(t_bash *data, char c, int pos);
int			get_win_max_col();
void		init_cursor(t_bash *data);
void		fill_term_struct(t_bash *data, t_term **cursor, char *str, int max);
t_term		*find_cursor_node(t_term **head, int idx, int idx_max, int plen);
void		clear_struct(t_term **cursor);
int			get_y_cursor(t_term *src);

/*
**	SELECT COPY CUT & PASTE
*/

void    	select_back(t_bash *data);
void    	select_next(t_bash *data);
void    	select_copy(t_bash *data);
void    	select_paste(t_bash *data);
void		uncolor(t_bash *data);
void		unselect(t_bash *data);
char		*str_add_sub(char *str, char *sub, int pos);

/*
**	DEBUG & UNIT_TEST
*/

void		debug_loop_try_termcaps(t_bash data);
int			handle_expend(t_bash *data, char *entry, int pos);
void		exec_onebyone(t_bash data);
void		currsor_info(t_term *curr, int count);
void		info(char *str);

/*
** REDIRECTIONS
*/

/*
**	STRUCT
*/

t_redirection   *new_redirection(t_vect *cmd, int flags);
void            free_redirection(t_redirection *redirection);

/*
** SET UP
*/

t_bash			*initialize_redirection_set_up_functions(t_bash *data);
void            set_up_pipe_redirection(t_redirection *new);
void            search_redirections_in_cmd(t_bash *data, t_vect *cmd);

/*
**  TOOLS
*/

int             search_right_fd(t_arg *arg, char *substring, int *error);
int				search_left_fd(t_arg *arg, int operator_index, int def, int *error);
char            *search_file_word(t_vect *cmd, t_arg *arg, int substring_index, int *error);
int     		is_stdout_and_stderr_redirection(int left_fd, int right_fd);
void		    set_up_stdout_and_stderr_redirection(t_vect *cmd, t_arg *arg,
				int substring_index, int *error);
/*
** EXECUTION
*/

void            handle_redirections(t_bash *data, t_redirection *redirection, int position);
static void 	execute_command(t_bash *data, t_vect *command, char **args_array);
void            restore_directions(t_redirection *redirection);

/*
**	BUILT-IN
*/
int 		    check_built_in(t_bash *data);
void			print_env(t_bash *data);
char			*findenv(char **env, char *name);
void			set_env(t_bash *data);
void			unset_env(t_bash *data);
int				is_env_key_exist(char **env, char *key);
void			change_directory(t_bash *data);

#endif
