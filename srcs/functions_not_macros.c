/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_not_macros.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/15 18:58:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int     command_is_piped(t_vect *command)
{
    if (command->separator == '|')
        return (TRUE);
    else
        return (FALSE);
}

int    fork_is_required(t_vect *command)
{
    if (command->builtin && !command_is_piped(command))
        return FALSE;
    else
        return TRUE;    
}

int    fork_failed(pid_t pid)
{
    if (pid < 0)
        return (TRUE);
    else
        return (FALSE);    
}

int    is_child(pid_t pid)
{
    if (pid == 0)
        return (TRUE);
    else
        return (FALSE);   
}

int     using_heredoc(t_vect *command)
{
    if (command->doc_string != NULL)
    {
        return TRUE;
    }
    else
        return FALSE;    
}
