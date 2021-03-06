/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:38:11 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:48:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

t_arg	*add_arg(t_arg **head, t_arg *new_arg)
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
