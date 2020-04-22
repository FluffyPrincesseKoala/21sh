/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:42:41 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/22 19:44:28 by cylemair         ###   ########.fr       */
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

void		push_entry(t_bash *data, char *entry)
{
	char	*tmp;

	tmp = NULL;
	if (data->iterator || data->vector->line)
		tmp = addchar(data->vector->line, entry[0], data->iterator);
	else
		tmp = ft_strndup(entry, 1);
	if (ft_strlen(data->vector->line))
		ft_strdel(&data->vector->line);
	data->vector->line = ft_strdup(tmp);
	ft_strdel(&tmp);
}

int		handle_new_entry(t_bash *data, char *entry, int pos)
{
	if (!data->vector->line)
		data->vector->line = ft_strndup(entry, 1);
	else
	{
		if (data->vector->down)
			pull_line(&data->vector);
		push_entry(&(*data), entry);
	}
	print_rest(data->vector->line, pos, NULL);
	goto_iterator(*data, ++pos);
	return (pos);
}
