/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:08:24 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

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
