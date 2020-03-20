/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:37:19 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/20 17:54:58 by cylemair         ###   ########.fr       */
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
# include <stdio.h>
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
# define SYNTAX         "Syntax error\n"
# define NOFOD			"No such file or directory\n"
# define E_CHDIR	    -1
# define LEFT			tputs(tgoto(tgetstr("le", NULL), 0 , 0), 1, ft_putchar)
# define RIGHT			tputs(tgoto(tgetstr("nd", NULL), 0 , 0), 1, ft_putchar)

typedef struct			s_vect
{
	char				**arg;
	struct s_vect		*next;
}						t_vect;

typedef struct			s_bash
{
	char				**env;
	char				**venv;
	char				*cmd;
	char				**args;
	t_vect				*cmds;
	char				*prompt;

	int					prompt_len;
	int					column_count;
	int					iterator;
	char				*cmd_in;
	char				*cmd_out;
}						t_bash;

typedef struct			s_built
{
	void				(*f)(struct s_sh *, struct s_vect *);
	char				*name;
}						t_built;

#endif
