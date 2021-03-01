/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:50:02 by koala             #+#    #+#             */
/*   Updated: 2021/02/19 17:59:38 by cylemair         ###   ########.fr       */
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
		last_arg_before_doomsday->next->previous = NULL;
		last_arg_before_doomsday->next = NULL;
	}
}

void		get_post_separator_args(
	t_bash *data, t_vect *cmd, t_arg *arg, int index)
{
	char			*substring;
	t_arg			*new;
	unsigned int	len;

	substring = NULL;
	new = NULL;
	len = ft_strlen(CONTENT);
	if (substring = ft_strsub(arg->content, index, len - index))
	{
		if (insert_new_arg(cmd, arg, substring))
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
				get_post_separator_args(data, current, arg, separator_idx + 1);
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
	char	*tmp;

	if ((tmp = ft_replace_substr(LINE, "\n", " \n")))
	{
		if (ft_arraylen(table = ft_strsplit(tmp, ' ')))
			words_as_args(table, data);
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
	if (!data->vector->doc_string && ft_strstr(data->vector->line, "<<"))
		here_doc(data);
	free_array(table);
	ft_strdel(&tmp);
}
