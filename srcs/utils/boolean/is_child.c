/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:19:41 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 18:19:50 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int    is_child(pid_t pid)
{
    if (pid == 0)
        return (TRUE);
    else
        return (FALSE);   
}
