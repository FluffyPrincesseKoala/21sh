/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:50:02 by koala             #+#    #+#             */
/*   Updated: 2021/01/06 18:15:06 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** récupérer les quote, créer args au fur et à mesure
** avoir une variable dans t_arg, qui indique si quote ou pas
** reparser pour les separateur en ignorant les args qui sont des quote
*/

static int	contains_sperator(char *str)
{
	int		i;
	int		j;
	char	*separator;

	i = 0;
	separator = ";\n|";
	while (str && str[i])
	{
		j = 0;
		while (separator[j])
		{
			if (str[i] == separator[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void		detach_args(t_vect *current, t_arg *last_arg_before_doomsday)
{
	if (last_arg_before_doomsday->next)
	{
		current->next = vect_new(last_arg_before_doomsday->next, NULL);
		last_arg_before_doomsday->next = NULL;
	}
}

void		get_post_separator_args(t_bash *data, t_arg *lst, int index, int len)
{
	char	*substring;
	t_arg	*new;

	substring = NULL;
	new = NULL;
	if (substring = ft_strsub(lst->content, index, len - index))
	{
		if (insert_new_arg(lst, substring))
			return ;
		ft_strdel(&substring);
	}
	data->error = MALLOC_ERROR;
}

void		parse_args(t_bash *data, t_vect *current)
{
	t_arg	*arg;
	unsigned int	i;
	unsigned int	len;
	unsigned int	separator_idx;

	i = 0;
	len = 0;
	separator_idx = 0;
	arg = current->args;
	while (arg)
	{
		if ((separator_idx = contains_sperator(CONTENT)) != -1
		&& !arg->quote)
		{
			current->separator = CONTENT[separator_idx];
			if ((len = ft_strlen(CONTENT)) != separator_idx + 1)
				get_post_separator_args(data, arg, separator_idx + 1, len);
			detach_args(current, arg);
			CONTENT = ft_strsub_free(&CONTENT, 0, separator_idx);
		}
		arg = arg->next;
	}
}

void		format_line(t_bash *data)
{
	t_vect	*loop;
	char	**table;

	if (array_len(table = ft_strsplit(LINE, ' ')))
	{
		words_as_args(table, data);
		free_array(table);
	}
	if (VECT->args && !data->error)
	{
		loop = VECT;
		while (loop)
		{
			parse_args(data, loop);
			loop = loop->next;
		}
	}
	else
		puterror(data->error);
}