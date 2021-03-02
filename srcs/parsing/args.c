/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 12:56:24 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void    free_all_args(t_arg **arg, int flag)
{
    if (arg && *arg)
    {
		if (flag == CHECK_PREV_ARGS)
		{
			if ((*arg)->previous)
				free_all_args(&(*arg)->previous, FALSE);
		}
        free_all_args(&(*arg)->next, flag);
        ft_strdel(&(*arg)->content);
        (*arg)->previous = NULL;
        (*arg)->next = NULL;
        (*arg)->content = NULL;
        free(*arg);
		*arg = NULL;
		arg = NULL;
    }
}

void    detach_arg(t_arg *arg, t_vect *cmd)
{
    if (cmd->args == arg)
        cmd->args = arg->next;
    if (arg->previous)
        arg->previous->next = arg->next;
    if (arg->next)
        arg->next->previous = arg->previous;
}

void del_one_arg(t_arg *arg, t_vect *cmd)
{
    detach_arg(arg, cmd);
    ft_strdel(&CONTENT);
    free(arg);
    arg = NULL;
}
