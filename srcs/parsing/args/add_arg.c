/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:38:11 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/10 12:46:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void		add_arg(t_arg **head, t_arg *new_arg)
{
	t_arg	*cursor;

	if (!*head)
		*head = new_arg;
	else
	{
		cursor = *head;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new_arg;
		new_arg->previous = cursor;
	}
}
