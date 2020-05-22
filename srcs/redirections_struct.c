/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/04 22:59:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void     insert_new_redirection(t_vect *cmd, t_redirection *new)
{
    if (cmd->redirection)
    {
        cursor = cmd->redirection;
        while (cursor->next)
            cursor = cursor->next;
        cursor->next = new;
    }
    else
        cmd->redirection = new;
}

t_redirection   *new_redirection(t_vect *cmd, int flags)
{
    t_redirection   *new;
    t_redirection   *cursor;

    if (!new = ft_memalloc(sizeof(t_redirection)))
        return NULL;
    new->flags = flags;
    insert_new_redirection(cmd, new);
    return (new);
}

void        free_redirection(t_redirection *redirection)
{
    if (redirection->next)
        free_redirection(redirection->next);
    redirection->next = NULL;
    ft_strdel(file_word);
    ft_strdel(operator);
    free(redirection);
}
