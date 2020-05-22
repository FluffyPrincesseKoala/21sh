/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/29 17:12:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int    fork_failed(pid_t pid)
{
    return (pid < 0);
}

int    is_child(pid_t pid)
{
    return (pid == 0)
}

int     error_occured(char *error)
{
    return (error[0] != NULL)
}
