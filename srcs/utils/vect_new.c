/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:08:24 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:27:58 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

t_vect	*vect_new(t_arg *args, char *line)
{
	t_vect	*list;

	list = (t_vect *)ft_memalloc(sizeof(t_vect));
	if (!list)
		return (NULL);
	if (args)
		list->args = args;
	else
		list->args = NULL;
	if (line)
		list->line = ft_strdup(line);
	else
		list->line = NULL;
	list->next = NULL;
	list->up = NULL;
	list->down = NULL;
	return (list);
}
