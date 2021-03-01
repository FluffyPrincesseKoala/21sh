/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:06:43 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/01 15:17:30 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H_
# define STRUCTS_H_

# define SLEFT	-1
# define SRIGHT	1
# define NOSLT	0

typedef struct					s_term
{
	int							line_start;
	int							x_max;
	int							line_len;
	char						*line;
	struct s_term				*next;
	struct s_term				*prev;
}								t_term;

typedef struct					s_arg
{
	char						*content;
	char						quote;
	struct s_arg				*previous;
	struct s_arg				*next;
}								t_arg;

typedef struct					s_redirection
{
	int							flags;
	int							left_fd;
	int							right_fd;
	int							backup_fd;
	char						*file_word;
	char						*op;
	struct s_redirection		*next;
}								t_redirection;

struct							s_bash;

typedef struct					s_heredoc
{
	char						**doc_strings;
	char						*eof;

	int							finish_heredoc;
	int							is_delim;
}								t_heredoc;

typedef struct					s_vect
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

typedef	void					(t_setup_ptr)(t_vect *, t_arg *,
								t_redirection *, int *);

typedef struct					s_redirection_setup
{
	t_setup_ptr					*f;
	char						*op;
	int							flags;
}								t_redirection_setup;

struct							s_built;

typedef struct					s_bash
{
	char						**env;
	char						**venv;
	int							error;
	char						*error_msg;
	struct	s_built				*builtin;
/*
**	CURSOR POSITION
*/
	t_term						*cursor;
	int							x;
	int							y;
	int							iterator;
	int							prompt_len;
/*
**	PARSING
*/
	t_vect						*vector;
	int							history_stack;
	int							count_separator;
	int							enclose;
	int							expend;
	int							start_expend;
	int							expend_up;
/*
**	SELECT COPY PASTE
*/
	int							start_select;
	int							is_select;
	int							select_direction;
	int							end_select;
	char						*copied;
/*
**	REDIRECT
*/
	struct s_redirection_setup  **redirections_setup;
/*
**	HERE DOCS
*/
	char						*doc_string;
	char						*eof;
	int							is_here_doc;
	int							nb_heredoc;
	int							finish_heredoc;
	int							here_doc_delimiter;
/*
** SYSCALLS
*/
	char						**args_array;
	char						*path;
}								t_bash;

typedef struct					s_built
{
	void						(*f)(struct s_bash *, struct s_vect *);
	int							len;
	char						*name;
}								t_built;

typedef struct					s_key
{
	void						(*f)(struct s_bash *);
	int							len;
	char						*name;
}								t_key;

#endif
