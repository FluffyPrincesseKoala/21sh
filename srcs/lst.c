/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 16:23:20 by cylemair          #+#    #+#             */
/*   Updated: 2020/05/09 16:45:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_lst		*lstnew(char *content)
{
	t_lst	*list;

	if (!(list = (t_lst*)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (content)
		list->content = ft_strdup(content);
	else
		list->content = NULL;
	list->next = NULL;
	return (list);
}

void		lstadd(t_lst **head, t_lst *new)
{
	if (head && *head && new)
	{
		if ((*head)->next)
			lstadd(&(*head)->next, new);
		else
			(*head)->next = new;
	}
	else
		*head = new;
}

void		lstfree(t_lst **head)
{
	if ((*head)->next)
		lstfree(&(*head)->next);
	if (head)
	{
		ft_strdel(&(*head)->content);
		free(*head);
		*head = NULL;
		head = NULL;
	}
}

static int	counter(t_lst *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char		**lst_to_array(t_lst *head)
{
	t_lst	*lst;
	char	**array;
	int		i;

	array = NULL;
	i = 0;
	if (head)
	{
		lst = head;
		if (!(array = malloc(sizeof(char*) * (counter(lst) + 1))))
			return (NULL);
		while (lst)
		{
			array[i] = ft_strdup(lst->content);
			lst = lst->next;
			i++;
		}
		array[i] = NULL;
	}
	return (array);
}
