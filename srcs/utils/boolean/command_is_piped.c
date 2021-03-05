/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_is_piped.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:18:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 18:18:37 by cylemair         ###   ########.fr       */
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
