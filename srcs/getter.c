/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:42:41 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/05 14:59:21 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		pull_line(t_vect **head)
{
	t_vect	*lst;

	if (head && *head)
	{
		lst = *head;
		while (lst->down)
			lst = lst->down;
		ft_strdel(&lst->line);
		lst->line = ft_strdup((*head)->line);
		*head = lst;
	}
}

void		push_entry(t_bash *data, char *entry, char **line, int pos)
{
	char	*tmp;

	tmp = NULL;
	if (data->iterator || *line)
		tmp = addchar(*line, entry[0], pos);
	else
		tmp = ft_strndup(entry, 1);
	if (ft_strlen(*line))
		ft_strdel(line);
	*line = ft_strdup(tmp);
	ft_strdel(&tmp);
}

/*
**	if !LINE		: create it
**	if VECT_DOWN	: pull_line
**	push_entry
**
**	fill t_term
**	print
**	go to cursor
*/

int		handle_new_entry(t_bash *data, char *entry, int pos)
{
	if (!data->vector->line)
		data->vector->line = ft_strndup(entry, 1);
	else
	{
		if (data->vector->down)
			pull_line(&data->vector);
		push_entry(data, entry, &data->vector->line, data->iterator);
	}
	SAVE_C;
	data->iterator = pos;
	print_rest(data->vector->line, pos, NULL);
	RESET_C;
	arrow_right(data);
	return (data->iterator);
}
