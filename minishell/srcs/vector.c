/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:18:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/02/06 14:13:31 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vect		*vect_new(char **arg)
{
	t_vect	*list;

	if (!(list = (t_vect*)malloc(sizeof(t_vect))))
		return (NULL);
	if (arg)
		list->arg = copy_array(arg);
	else
		list->arg = NULL;
	list->next = NULL;
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

	if (head)
	{
		lst = *head;
		while (lst)
		{
			free_array(lst->arg);
			lst_next = lst->next;
			free(lst);
			lst = lst_next;
		}
	}
}

void		vect_print(t_vect *lst)
{
	if (lst)
	{
		putab(lst->arg);
		vect_print(lst->next);
	}
}
