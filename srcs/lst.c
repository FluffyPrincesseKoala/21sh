/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 16:23:20 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/03 19:01:25 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_lst		*lstnew(char *content, int quote)
{
	t_lst	*list;

	if (!(list = (t_lst*)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (content)
		list->content = ft_strdup(content);
	else
		list->content = NULL;
	list->quote = quote;
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

void		lst_add_after(t_lst *this_one, t_lst *next)
{
	t_lst	*after_next;

	if (this_one && next)
	{
		next->next = this_one->next;
		this_one->next = next;
	}
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
		if (lst->content)
			i++;
		lst = lst->next;
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
			if (lst->content)
			{
				array[i] = ft_strdup(lst->content);
				i++;
			}
			lst = lst->next;
		}
		array[i] = NULL;
	}
	return (array);
}
