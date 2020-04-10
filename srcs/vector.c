/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 19:25:39 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/06 21:24:53 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_vect		*vect_new(char **arg, char *line)
{
	t_vect	*list;

	if (!(list = (t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	list->arg = (arg) ? copy_array(arg) : NULL;
	list->line = (line) ? ft_strdup(line) : NULL;
	list->next = NULL;
	list->up = NULL;
	list->down = NULL;
	return (list);
}

t_vect		*vect_add(t_vect **head, t_vect *new)
{
	t_vect	*tmp;

	if (head)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*head);
}

void		free_vector(t_vect **head)
{
	t_vect	*lst;
	t_vect	*lst_next;

	// free all pts first
	// recurse on lst->next
	// memset ton vecteur à 0
	// free(lst)

	if (head)
	{
		lst = *head;
		while (lst)
		{
			if (lst->arg)
			{
				free_array(lst->arg);
				lst->arg = NULL;
			}
			ft_strdel(&lst->line);
			lst->line = NULL;
			lst_next = lst->next;
			free(lst);
			lst = lst_next;
		}
	}
}

t_vect		*vect_push(t_vect **head, t_vect *new)
{
	t_vect	*lst;

	lst = NULL;
	if (head && *head)
	{
		lst = *head;
		while (lst->down)
			lst = lst->down;
		lst->down = new;
		new->up = lst;
		return (new);
	}
	else
		return (new);
}

size_t		count_lst(t_vect *head)
{
	t_vect	*lst;
	size_t	count;

	count = 0;
	lst = head;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_vect		*link_history(t_vect **head, t_vect *new)
{
	t_vect	*lst;

	if (head && *head)
	{
		lst = *head;
		lst->down = (new) ? new : vect_new(NULL, NULL);
		lst->down->up = lst;
		if (lst->up)
			lst->up->down = lst;
		lst = lst->down;
		return (lst);
	}
	return (new);
}
