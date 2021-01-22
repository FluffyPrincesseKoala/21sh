/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/22 16:24:11 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions related to redirection chained list manipulation
*/

/*
** Insert the given redirection structure at the end of the command redirections
**  chained list.
*/

static void     insert_new_redirection(t_vect *command, t_redirection *new)
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

t_redirection   *new_redirection(t_vect *command, int flags)
{
    t_redirection   *new;
    t_redirection   *cursor;

    if (!(new = ft_memalloc(sizeof(t_redirection))))
        return (NULL);
    new->flags = flags;
    insert_new_redirection(command, new);
    return (new);
}

/*
** Free the whole redirections chained list, set pointers to null.
*/

void        free_redirection(t_redirection *redirection)
{
    if (redirection->next)
        free_redirection(redirection->next);
    redirection->next = NULL;
    ft_strdel(&redirection->file_word);
    ft_strdel(&redirection->op);
    free(redirection);
}
