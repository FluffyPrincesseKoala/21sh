/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 13:39:31 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		print_args(t_bash *data, t_vect *command)
{
	t_arg	*arg;

	if (command->args)
		arg = command->args->next;
	while (arg)
	{
		ft_putstr(arg->content);
		if (arg->next)
			ft_putchar(' ');
		arg = arg->next;
	}
	ft_putchar('\n');
}

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

void del_one_arg(t_arg *arg, t_vect *cmd)
{
    detach_arg(arg, cmd);
    ft_strdel(&CONTENT);
    free(arg);
    arg = NULL;
}
