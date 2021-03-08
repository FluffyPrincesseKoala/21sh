/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_new_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:37:12 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/08 18:52:16 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int	insert_new_arg(t_vect *command, t_arg *previous, char *s)
{
	t_arg	*new;

	if (!(new = create_arg(s, NULL)))
		return (FAIL);
	if (previous)
	{
		new->next = previous->next;
		new->previous = previous;
		previous->next = new;
		if (new->next)
			new->next->previous = new;
		return (SUCCESS);
	}
	else
	{
		new->next = command->args;
		command->args->previous = new;
		command->args = new;
	}
	return (-1);
}
