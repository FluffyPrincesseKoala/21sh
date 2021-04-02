/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:30:48 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:29:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	insert_first_redirection(t_vect *command, t_redirection *new)
{
	new->next = command->redirections;
	command->redirections = new;
}

/*
** Insert the given redirection structure at the end of the command redirections
**  chained list.
*/

static void	insert_new_redirection(t_vect *command, t_redirection *new)
{
	t_redirection	*cursor;

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

t_redirection	*new_redirection(t_vect *command, int first)
{
	t_redirection	*new;
	t_redirection	*cursor;

	new = ft_memalloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	if (first)
		insert_first_redirection(command, new);
	else
		insert_new_redirection(command, new);
	return (new);
}
