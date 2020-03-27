/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:42:41 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/24 20:31:38 by cylemair         ###   ########.fr       */
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
	if ((*data).iterator || (*data).vector->line)
		tmp = addchar((*data).vector->line, entry[0], (*data).iterator);
	else
		tmp = ft_strndup(entry, 1);
	ft_strdel(&(*data).vector->line);
	(*data).vector->line = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void		handle_new_entry(t_bash *data, char *entry)
{
	if (!(*data).vector->line)
		(*data).vector->line = ft_strndup(entry, 1);
	else
	{
		if ((*data).vector->down)
			pull_line(&(*data).vector);
		push_entry(&(*data), entry);
	}
	print_rest((*data).vector->line, (*data).iterator, NULL);
	(*data).iterator++;
	goto_iterator((*data));
}