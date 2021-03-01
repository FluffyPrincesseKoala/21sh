/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 19:25:39 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/19 18:56:17 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_vect		*vect_new(t_arg *args, char *line)
{
	t_vect	*list;

	if (!(list = (t_vect*)ft_memalloc(sizeof(t_vect))))
		return (NULL);
	list->args = (args) ? args : NULL;
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

void		free_all_vectors(t_vect *vect)
{
	if (vect)
	{
		ft_strdel(&vect->line);
		ft_strdel(&vect->eof);
		free_array(vect->doc_string);
		free_all_args(&vect->args, FALSE);
		free_all_vectors(vect->next);
		free_all_vectors(vect->up);
		if (vect->redirections)
			free_redirections(vect);
		vect->args = NULL;
		vect->next = NULL;
		vect->up = NULL;
		vect->down = NULL;
		vect->redirections = NULL;
		vect->line = NULL;
		free(vect);
		vect = NULL;
	}
}

void		free_vector(t_vect **head, int flag)
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
			if (lst->args)
				free_all_args(&lst->args, flag);
			lst->args = NULL;
			ft_strdel(&lst->line);
			free_array(lst->doc_string);
			lst->line = NULL;
			lst_next = lst->next;
			free(lst);
			lst = NULL;
			lst = lst_next;
		}
		head = NULL;
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
