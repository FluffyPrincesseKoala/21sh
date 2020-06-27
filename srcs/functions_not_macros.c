/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_not_macros.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/12 15:33:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

int     error_occured(char *error)
{
    if (error[0] != '\0')
        return (TRUE);
    
    else
        return (FALSE);
}
