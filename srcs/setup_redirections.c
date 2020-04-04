/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 22:59:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static t_redirection    *create_redirection(t_vect *cmd)
{
    t_redirection   *new;
    t_redirection   *cursor;

    if (!new = ft_memalloc(sizeof(t_redirection)))
        return false;
    if (cmd->redirection)
    {
        cursor = cmd->redirection;
        while (cursor->next)
            cursor = cursor->next;
        cursor->next = new;
    }
    else
        cmd->redirection = new;
    return (new);
}

void                    set_up_in_redirection(t_vect *cmd, char *in_fd)
{
    t_redirection *redirection;

    redirection = create_redirection(cmd);
    redirection->in_fd = ft_atoi(in_fd);
}

void                    set_up_out_redirection(t_vect *cmd, char *out_fd)
{
    t_redirection *redirection;

    redirection = cmd->redirection;
    if (redirection)
        while (redirection->next)
            redirection = redirection->next;
    else
        redirection = create_redirection(cmd);
    redirection->out_fd = ft_atoi(out_fd);
}

void                    set_up_file_redirection(t_vect *cmd, char *file)
{
    t_redirection *redirection;

    redirection = cmd->redirection;
    if (redirection)
        while (redirection->next)
            redirection = redirection->next;
    else
        redirection = create_redirection(cmd);
    redirection->opened_file = ft_strdup(file);
}