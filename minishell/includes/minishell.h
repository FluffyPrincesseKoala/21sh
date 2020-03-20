/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:36:43 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 20:24:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <stdio.h>
# include "../libft/get_next_line.h"
# include "../libft/libft.h"

# define RED 	    	"\033[1;31m"
# define RESET		    "\033[0m"
# define NODIR	    	"Not a directory\n"
# define DENY		    "Permission denied\n"
# define UNOW		    "Command not found\n"
# define SYNTAX         "Syntax error\n"
# define NOFOD			"No such file or directory\n"
# define E_CHDIR	    -1

typedef struct			s_vect
{
	char				**arg;
	struct s_vect		*next;
}						t_vect;

typedef struct			s_sh
{
	char				**env;
	char				**venv;
	char				*cmd;
	char				**args;
	t_vect				*cmds;
	char				*prompt;
}						t_sh;

typedef struct			s_built
{
	void				(*f)(struct s_sh *, struct s_vect *);
	char				*name;
}						t_built;

char					**copy_array(char **array);
char					*findenv(char	**env, char *var);
char					**delenv(char **env, char *var);
char					**addenv(char **env, char *var);
char					**change_key(char **env, char *var);
char					**update_key(char **env, char *up,
									char *key, char *dest);
char					*build_path(t_sh ell, t_vect *lst);
int						exec_cmd(t_sh ell, char *path, t_vect *cmd);
void					read_stdin(t_sh ell);
void					change_dir(const char *path, t_sh *ell);
int						check_builtin(t_sh *ell, t_vect *cmd);
void					get_var(t_vect **head, char **env);
void					tilt(t_vect **head, t_sh ell);
void					builtin_env(t_sh *ell, t_vect *cmd);
void					builtin_unsetenv(t_sh *ell, t_vect *cmd);
void					builtin_setenv(t_sh *ell, t_vect *cmd);
void					builtin_cd(t_sh *ell, t_vect *cmd);
void					builtin_echo(t_sh *ell, t_vect *cmd);
void					putab(char **array);
void					puterror(char *error);
int						array_len(char **array);
size_t					count_delim(char *str, int delim);
void					streplace(char **s1, char **s2);
char					*str_remove(char *str, char delim);
char					*replace_delim(char *str, char delim, char new);
int						array_total_len(char **array);
void					free_array(char **array);
t_vect					*vect_new(char **arg);
t_vect					*vect_add(t_vect **head, t_vect *new);
void					free_vector(t_vect **head);
void					vect_print(t_vect *lst);
size_t					count_lst(t_vect *head);
int						lendelim(char *str, char delim, int start);
int						array_cmp(char **a, char **b);

#endif
