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
# define REDIRECTIONS_SETUP data->redirections_setup
# define EOF_IDX			vector->eof_idx
# define CUR_EOF			vector->eof[vector->eof_idx]
# define CUR_X				(data->iterator + data->prompt_len) % w.ws_col
# define CUR_Y		    	(data->iterator + data->prompt_len) / w.ws_col
# define LEN_Y				(ft_strlen(LINE) + data->prompt_len) / w.ws_col
# define ONLY_WCHAR			(count_delim(LINE, ' ') != ft_strlen(LINE))
# define UP					term_put("up")
# define CDOWN				term_put("do")
# define LEFT				term_put("le")
# define RIGHT				term_put("nd")
# define SAVE_C				term_put("sc")
# define RESET_C			term_put("rc")
# define CLEAR				tputs(tgetstr("cl", NULL), 1, &pchar)
# define GOTO(X,Y)			tputs(tgoto(tgetstr("cm", NULL), X, Y), 1, &pchar)
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
t_bash	*data_g;

/*
**	t_vect manipulation (keep current and old entry)
*/

t_vect		*vect_new(t_arg *args, char *line);
t_vect		*vect_add(t_vect **head, t_vect *new);
t_vect		*vect_push(t_vect **head, t_vect *new);
size_t		count_arg(t_vect *head);
t_vect		*link_history(t_vect **head, t_vect *new);
void		free_vector(t_vect **head, int flag);

/*
**	ARRAY FORMATING
*/

int			ft_arraylen(char **array);
void		print_array(char **array);
char		**array_add_value(char **src, char *value);
char		**change_array_value(char **src, char *key, char *value);
char		**create_array(char *first);

/*
**	STDIN & TERM RELATED
*/

void		term_put(char *esc);

void		arrow_key(t_bash *data, char *buff);

void		key_last(t_bash *data);
void		key_start(t_bash *data);
void		key_back(t_bash *data);
void		key_suppr(t_bash *data);

/*
**	STRING FORMATING
*/
char		*addchar(char *str, char c, int pos);
char		*replace_delim(char *str, char delim, char new);
int			pstr(char const *str);
int			pchar(int c);
size_t		count_delim(char *str, int delim);
char		*replace_delim(char *str, char delim, char new);
char		*ft_replace_substr(char *str, char *old, char *new);
char		*merge_string_from_array(char **src, int size, int start);
char		**split_all_whitespace(char const *s);

/*
**	OTHER STUFF
*/

void		hello();
int			prompt(char **env, int short_prompt);
void		loop(t_bash *data);
void		handle_fork(t_bash *data, t_vect *cmd);
int			print_rest(char *str, int pos, char *old);
void		puterror(int error);
void 		set_up_signals();
void		put_error_msg(char *error);
void		*free_bash(t_bash *data);

/*
**	PARSING
*/

int			next_delim(char **array, int start);
void		read_separator(char **table, t_bash *data);
void		format_line(t_bash *data);
size_t		count_delim(char *str, int delim);
int			pending_line(char *str);
void		words_as_args(char **table, t_bash *data);

/*
**	LIST STUFF
*/

void		free_all_vectors(t_vect *vect);

/*
**	CURSOR TERM STRUCT
*/

void		charadd_to_term(t_bash *data, char c, int pos);

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
**	ERROR MANAGEMENT
*/

void		print_failed_fork_error(pid_t pid);
void		error_code_to_message(int *error);






/*
** ========
**  SET UP
** ========
*/

/*
** Initialize t_bash
*/
char		**copy_env(char **array);
int			init_built_in(t_built **fct);
int			init_redirection_set_up_functions(t_bash *data);

/*
** ===========
**  TERM CAPS
** ===========
*/

void		arrow_down(t_bash *data);
void		arrow_left(t_bash *data);
void		arrow_right(t_bash *data);
void		arrow_up(t_bash *data);

void		move_left(t_bash *data);
void		move_right(t_bash *data);

/*
** Ctrl Key
*/
void		ctrl_down(t_bash *data);
void		ctrl_left(t_bash *data);
void		ctrl_right(t_bash *data);
void		ctrl_up(t_bash *data);
void        init_xy(t_bash *data, int *x, int *y, int max);

/*
** Cursor
*/
void		set_cursors(t_bash *data, t_term **cursor, char *str, int max);
t_term		*find_cursor_node(t_term **head, int idx, int idx_max, int plen);

/*
** Conf
*/
int			conf_term();
void		unconf_term();
void		reset_conf_term();

/*
** Tools
*/
int			get_win_max_col();

/*
** =========
**  STDIN
** =========
*/

int			    ft_strlendelim(char *str, char delim, int start);
void		    get_var(t_arg **head, char **env);
int			    handle_new_entry(t_bash *data, char *entry, int pos);
void		    pull_line(t_vect **head);
void		    push_entry(t_bash *data, char *entry, char **line, int pos);
char		    *unquote(char *str, char delim);
char			*use_shell_var(char **env, char *str);

/*
** Args
*/
t_arg  		    *add_arg(t_arg **head, t_arg *new);
t_arg   	    *create_arg(char *content, char quote);
int    		    insert_new_arg(t_vect *command, t_arg *previous, char *s);


/*
** End of line
*/
int				format_line_required(t_bash *data);
int   		    end_of_line(t_bash **data);

/*
** ===========
**	BUILT-INS
** ===========
*/

void			change_directory(t_bash *data, t_vect *command);
void			print_args(t_bash *data, t_vect *command);
void			print_env(t_bash *data, t_vect *cmd);
void			set_env(t_bash *data, t_vect *command);
void			unset_env(t_bash *data, t_vect *command);
char			*get_env_var_value(char **env, char *name);
int				is_env_key_exist(char **env, char *key);
void			print_history(t_bash *data);
void			history(t_bash *data, t_vect *cmd);

/*
** ===========
**	HEREDOC
** ===========
*/

void			custom_return(void);
void			clean_screen(t_bash *data);
void			return_exit(t_bash *data);
int				update_heredoc(t_bash *data);
void			here_doc(t_bash *data);
void			fill_heredoc_array(t_bash *data, t_vect *cmd, char **line);
int				parse_newline_as_heredoc(t_vect **head, t_bash *data);


/*
** ===========
**  EXECUTION
** ===========
*/

void			execute_command(t_bash *data, t_vect *command);
int         	handle_commands(t_bash *data, t_vect *command);
int         	handle_execution(t_bash *data, t_vect *command);
void			search_built_in(t_bash *data, t_vect *command);

/*
** Syscalls
*/
char    	    **arg_to_array(t_bash *data, t_arg *arg);
char		    *choose_command_path(t_bash *data, char *command_name);
void 			execute_syscall(t_bash *data, t_vect *command);

/*
** Redirections
*/
int           	execute_redirections(t_bash *data, t_vect *command, t_redirection *redirection);
t_redirection	*new_redirection(t_vect *cmd, int flags);
char            *search_file_word(t_vect *cmd, t_arg *arg, int substring_index, int *error);
int				search_left_fd(t_vect *cmd, t_arg *arg, int def, int *error);
int             search_right_fd(t_vect *cmd, t_arg *arg, char *substring, int *error);
int				set_up_command_redirections(t_bash *data, t_vect *cmd);
void            restore_directions(t_redirection *redirection);

/*
** Pipe
*/
void			handle_heredoc(t_bash *data, t_vect *command);
int 			handle_pipe(t_bash *data, t_vect *command);
void        	pipe_fork(t_bash *data, t_vect *command, int pipe_fd[2], int heredoc);
void        	set_stdin_pipe_redirection(t_vect *command, int pipe_fd[2]);
void			write_heredoc(t_bash *data, t_vect *command, int pipe_fd[2]);

/*
** Boolean tools
*/
int     		command_is_piped(t_vect *command);
int		        fork_is_required(t_vect *command);
int			    fork_failed(pid_t pid);
int			    is_child(pid_t pid);
int				is_exit(t_vect *command);
int     		is_stdout_and_stderr_redirection(int left_fd, int right_fd);
int     	    using_heredoc(t_vect *command);

/*
** ==========
**  CLEAN UP
** ==========
*/

void		    clear_struct(t_term **cursor);
void		    del_one_arg(t_arg *arg, t_vect *cmd);
void		    detach_arg(t_arg *arg, t_vect *cmd);
void    	    free_all_args(t_arg **arg, int flag);
void		    free_array(char **array); 
void			free_builtin(t_built **fct);
void			free_redirections(t_vect *command);

/*
** ===================
**	DEBUG & UNIT_TEST
** ===================
*/

void		currsor_info(t_term *curr, int count);
void		info(char *str);

#endif
