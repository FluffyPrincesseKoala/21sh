/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:42:44 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:39:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	free_all_args(t_arg **arg, int flag)
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
