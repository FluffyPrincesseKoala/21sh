/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 17:30:01 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	free_key(t_key **fct)
{
	int	i;

	i = 0;
	while (i != MAX_KEY)
	{
		(*fct)[i].f = NULL;
		ft_strdel(&(*fct)[i].name);
		(*fct)[i].name = NULL;
		i++;
	}
	free(*fct);
	*fct = NULL;
	fct = NULL;
}

void		termi(t_bash *data, char *buff)
{
	static t_key	*fct;
	int				i;
	int				exit;

	i = 0;
	exit = 0;
	if (!buff && !data)
	{
		if (fct)
			free_key(&fct);
		return ;
	}
	if (!fct)
		init_key_functions(&fct);
	while (i != MAX_KEY && !exit)
	{
		if (ft_strnequ(buff, fct[i].name, fct[i].len))
		{
			fct[i].f(data);
			exit++;
		}
		i++;
	}
}
