/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:59:39 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:28:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	pull_line(t_vect **head)
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
