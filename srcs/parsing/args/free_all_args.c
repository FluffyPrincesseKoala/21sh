/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:42:44 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/08 20:27:18 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

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
		ft_strdel(&(*arg)->quoted);
		(*arg)->previous = NULL;
		(*arg)->next = NULL;
		(*arg)->content = NULL;
		(*arg)->quoted = NULL;
		free(*arg);
		*arg = NULL;
		arg = NULL;
	}
}
