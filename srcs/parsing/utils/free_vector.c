/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:12:01 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

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
