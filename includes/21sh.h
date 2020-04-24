/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:37:19 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/24 17:20:23 by cylemair         ###   ########.fr       */
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
//#include <curses.h>

# include "../libft/get_next_line.h"
# include "../libft/libft.h"

# define BLUE			"\033[38;5;61m"
# define GREEN			"\033[38;5;29m"
# define CYAN			"\033[38;5;50m"
# define RED 	    	"\033[1;31m"
# define RESET		    "\033[0m"
# define NODIR	    	"Not a directory\n"
# define DENY		    "Permission denied\n"
# define UNOW		    "Command not found\n"
# define SYNTAX         "21sh: syntax error near unexpected symbol "
# define NOFOD			"No such file or directory\n"
# define E_CHDIR	    -1
# define LINE		    data->vector->line
# define VECT		    data->vector
# define VECT_UP	    data->vector->up
# define VECT_DOWN	    data->vector->down
# define CUR_X		    (data->iterator + data->prompt_len) % w.ws_col
# define CUR_Y		    (data->iterator + data->prompt_len) / w.ws_col
# define LEN_Y			(ft_strlen(LINE) + data->prompt_len) / w.ws_col
# define ONLY_WCHAR		(count_delim(LINE, ' ') != ft_strlen(LINE))
# define UP				tputs(tgoto(tgetstr("up", NULL), 0 , 0), 1, &pchar)
# define CDOWN			tputs(tgoto(tgetstr("do", NULL), 0 , 0), 1, &pchar)
# define LEFT			tputs(tgoto(tgetstr("le", NULL), 0 , 0), 1, &pchar)
# define RIGHT			tputs(tgoto(tgetstr("nd", NULL), 0 , 0), 1, &pchar)
# define SAVE_C			tputs(tgoto(tgetstr("sc", NULL), 0 , 0), 1, &pchar)
# define RESET_C		tputs(tgoto(tgetstr("rc", NULL), 0 , 0), 1, &pchar)
# define CLEAR			tputs(tgetstr("cl", NULL), 1, &pchar)

typedef struct			s_vect
{
	char				*line;
	char				**arg;

	struct s_vect		*next;
	struct s_vect		*up;
	struct s_vect		*down;
}						t_vect;

typedef struct			s_bash
{
	char				**env;
	char				**venv;
	t_vect				*vector;
	int					iterator;
	char				*error;

	int					prompt_len;
	int					count_separator;
}						t_bash;

typedef struct			s_built
{
	void				(*f)(struct s_bash *, struct s_vect *);
	char				*name;
}						t_built;

typedef struct			s_key
{
	void				(*f)(struct s_bash *);
	char				*name;
}						t_key;

/*
**	t_vect manipulation (keep current and old entry)
*/

t_vect		*vect_new(char **arg, char *line);
t_vect		*vect_add(t_vect **head, t_vect *new);
t_vect		*vect_push(t_vect **head, t_vect *new);
size_t		count_lst(t_vect *head);
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

/*
**	STDIN & TERM RELATED
*/

int			init_term();
int			conf_term();
int			handle_new_entry(t_bash *data, char *entry, int pos);
int			goto_iterator(t_bash data, int pos);

void		arrow_key(t_bash *data, char *buff);

void		key_last(t_bash *data);
void		key_start(t_bash *data);
void		key_back(t_bash *data);
void		key_suppr(t_bash *data);

void		ctrl_right(t_bash *data);
void		ctrl_left(t_bash *data);

void		arrow_left(t_bash *data);
void		arrow_right(t_bash *data);
void		arrow_down(t_bash *data);
void		arrow_up(t_bash *data);

/*
**	STRING FORMATING
*/

char		*addchar(char *str, char c, int pos);
int			pstr(char const *str);
int			pchar(int c);
size_t		count_delim(char *str, int delim);
char		*replace_delim(char *str, char delim, char new);
char		*replace_substr(char *str, char *old, char *new);

/*
**	OTHER STUFF
*/

void		hello();
int			prompt();
t_vect		*format_line(t_bash *data);
void		loop(t_bash *data);
char		*build_path(t_bash data, t_vect *lst);
int			exec_cmd(t_bash data, char *path, t_vect *cmd);
int			print_rest(char *str, int pos, char *old);

/*
**	DEBUG & UNIT_TEST
*/

void		debug_loop_try_termcaps(t_bash data);

#endif
