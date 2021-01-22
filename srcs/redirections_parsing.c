/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:16:22 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/22 16:25:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions relative to finding redirections in submitted
**  command and call appropriate functions to set it up for the execution.
*/

/*
** Search for redirection operator in given argument.
** Return a redirection setup structure that associate each redirection operator
**  with its set up function and file-opening flag.
*/

static t_redirection_setup  *parse_redirections_in_arg(
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

/*
** Search for redirections in the given command.
** Whe it finds one, remove the concerned argument and call the appropriate set
**  up function.
** Loop the function on the next command.
*/

void                        set_up_command_redirections(
    t_bash *data, t_vect *command)
{
    t_redirection_setup *redirection_setup;
    t_redirection       *new;
    t_arg               *arg;

    arg = command->args;
    while (arg)
    {
        if (redirection_setup = parse_redirections_in_arg(
            REDIRECTIONS_SETUP, CONTENT))
        {
            new = new_redirection(command, redirection_setup->flags);
            redirection_setup->f(command, arg, new, &(data->error));
            del_one_arg(arg, command);
            arg = command->args;
        }
        else
            arg = arg->next;
        if (data->error)
            arg = NULL;
    }
    if (command->next)
        set_up_command_redirections(data, command->next);
}