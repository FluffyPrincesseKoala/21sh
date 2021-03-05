/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:42:20 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:35:58 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	detach_arg(t_arg *arg, t_vect *cmd)
{
	if (cmd->args == arg)
		cmd->args = arg->next;
	if (arg->previous)
		arg->previous->next = arg->next;
	if (arg->next)
		arg->next->previous = arg->previous;
}
