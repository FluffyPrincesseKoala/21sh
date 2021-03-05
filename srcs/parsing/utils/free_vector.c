/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:12:01 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 18:07:05 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		free_vector(t_vect **head, int flag)
{
	t_vect	*lst;
	t_vect	*lst_next;

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
