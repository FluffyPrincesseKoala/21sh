/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:38:11 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:33:16 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_arg	*add_arg(t_arg **head, t_arg *new)
{
	t_arg	*cursor;

	if (!*head)
		*head = new;
	else
	{
		cursor = *head;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
		new->previous = cursor;
	}
}
