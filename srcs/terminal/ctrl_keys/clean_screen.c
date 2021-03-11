/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:41:14 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/11 19:35:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void		clean_screen(t_bash *data)
{
	clear();
	prompt(data->env, 0);
	if (data->expend)
	{
		ft_putendl(data->vector->up->line);
		prompt(data->env, data->expend);
	}
	ft_putstr(data->vector->line);
}
