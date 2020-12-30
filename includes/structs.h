/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:06:43 by cylemair          #+#    #+#             */
/*   Updated: 2020/12/30 14:49:30 by koala            ###   ########.fr       */
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
	int							quote;
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

typedef struct					s_vect
{
	char						*line;
	t_arg						*args;
	char						separator;
	t_redirection				*redirections;

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

typedef struct					s_bash
{
	char						**env;
	char						**venv;
	int							error;
	char						*error_msg;
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