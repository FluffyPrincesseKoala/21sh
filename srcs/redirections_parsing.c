/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:16:22 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/10 13:56:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"


t_redirection_setup    *search_redirections_in_arg(
    t_redirection_setup **redirections_set_up, char *arg)
{
    int     i;

    if (arg)
    {
        i = 0;
        while (redirections_set_up[i])
        {
            if (ft_strstr(arg, redirections_set_up[i]->op))
                return (redirections_set_up[i]);
            i++;
        }
    }
    return (NULL);
}

void                search_redirections_in_cmd(t_bash *data, t_vect *cmd)
{
    t_redirection_setup *setup_redirection;
    t_arg               *arg;

    arg = cmd->args;
    if (cmd->separator == '|')
        set_up_pipe_redirection(new_redirection(cmd, 0));
    while (arg)
    {
        if (setup_redirection = search_redirections_in_arg(
            REDIRECTION_SETUP, CONTENT))
        {
            setup_redirection->f(
                cmd, arg, new_redirection(cmd, setup_redirection->flags), &(data->error));
            del_one_arg(arg, cmd);
            arg = cmd->args;
        }
        else
            arg = arg->next;
        if (data->error)
            arg = NULL;
    }
    if (cmd->next)
        search_redirections_in_cmd(data, cmd->next);
}