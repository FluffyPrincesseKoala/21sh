/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:06:43 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:25:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define SLEFT	-1
# define SRIGHT 1
# define NOSLT	0

typedef struct s_term
{
	int				line_start;
	int				x_max;
	int				line_len;
	char			*line;
	struct s_term	*next;
	struct s_term	*prev;
}					t_term;

typedef struct s_arg
{
	char			*content;
	char			*quoted;
	struct s_arg	*previous;
	struct s_arg	*next;
}					t_arg;

struct	s_redirection_setup;

typedef struct s_redirection
{
	int							left_fd;
	int							right_fd;
	int							backup_fd;
	char						*file_word;
	t_arg						*arg;
	struct s_redirection_setup	*setup;
	struct s_redirection		*next;
}								t_redirection;

struct	s_bash;

typedef struct s_vect
{
	char						*line;
	t_arg						*args;

	char						separator;

	char						**doc_string;
	char						*eof;
	int							is_delim;

	t_redirection				*redirections;
	void						(*builtin)(struct s_bash *, struct s_vect *);

	struct s_vect				*next;
	struct s_vect				*up;
	struct s_vect				*down;
}								t_vect;

typedef	void (t_setup_ptr)(t_vect *, t_arg *, t_redirection *, int *);

typedef struct s_redirection_setup
{
	t_setup_ptr					*f;
	char						*op;
	int							flags;
}								t_redirect_setup;

struct	s_built;

typedef struct s_bash
{
	char						**env;
	char						**venv;
	int							error;
	char						*error_msg;
	struct s_built				*builtin;

	t_term						*cursor;
	int							x;
	int							y;
	int							iterator;
	int							prompt_len;

	t_vect						*vector;
	int							history_stack;
	int							count_separator;
	int							enclose;
	int							expend;
	int							start_expend;
	int							expend_up;

	int							start_select;
	int							is_select;
	int							select_direction;
	int							end_select;
	char						*copied;

	struct s_redirection_setup	**redirect_setup;

	char						*doc_string;
	char						*eof;
	int							is_heredoc;
	int							nb_heredoc;
	int							finish_heredoc;
	int							heredoc_delimiter;

	char						**args_array;
	char						*path;
	int							started;
}								t_bash;

typedef struct s_built
{
	void						(*f)(struct s_bash *, struct s_vect *);
	int							len;
	char						*name;
}								t_built;

typedef struct s_key
{
	void						(*f)(struct s_bash *);
	int							len;
	char						*name;
}								t_key;

#endif
