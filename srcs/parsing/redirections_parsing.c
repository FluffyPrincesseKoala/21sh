/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:16:22 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 19:25:05 by cylemair         ###   ########.fr       */
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

void    parse_redirection_in_arg(t_bash *data, t_vect *cmd, t_arg *arg)
{
    int             i;
    char            *op;
    t_redirection   *new;
    
    i = 0;
    while (data->redirections_setup[i])
    {
        if (op = ft_strstr(arg->content, data->redirections_setup[i]->op))
        {
            if (!(op[0] == '<' && op[1] == '<'))
            {
                new = new_redirection(cmd);
                new->setup = data->redirections_setup[i];
                new->arg = arg;
                break;
            }
        }
        i++;
    }
}

/*
** Search for redirections in the given command.
** Whe it finds one, remove the concerned argument and call the appropriate set
**  up function.
** Loop the function on the next command.
*/

int                        set_up_command_redirections(
    t_bash *data, t_vect *command)
{
    t_redirection       *redirection;

    redirection = command->redirections;
    while (redirection)
    {
        if (redirection->arg)
        {
            redirection->setup->f(command, redirection->arg, redirection, &(data->error));
            del_one_arg(redirection->arg, command);
        }
        else
            redirection = redirection->next;
        if (data->error)
            return (FAIL);
        redirection = redirection->next;
    }
    return (SUCCESS);
}

