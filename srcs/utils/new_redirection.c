/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:30:48 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Insert the given redirection structure at the end of the command redirections
**  chained list.
*/

static void		insert_new_redirection(t_vect *command, t_redirection *new)
{
	t_redirection *cursor;

	if (command->redirections)
	{
		cursor = command->redirections;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
	else
		command->redirections = new;
}

/*
** Create a new redirection structure with given flags, and insert it in the
**  command structure.
*/

t_redirection	*new_redirection(t_vect *command)
{
	t_redirection	*new;
	t_redirection	*cursor;

	if (!(new = ft_memalloc(sizeof(t_redirection))))
		return (NULL);
	insert_new_redirection(command, new);
	return (new);
}
