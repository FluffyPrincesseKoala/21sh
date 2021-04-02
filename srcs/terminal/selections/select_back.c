/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:32:59 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:01:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	reset_back(t_bash *data)
{
	data->end_select -= 1;
	data->is_select = 0;
	arrow_left(data);
	term_put(SAVE);
	ft_putchar(data->vector->line[data->end_select]);
	term_put(RESET_C);
	data->is_select = SRIGHT;
	if (data->end_select == data->start_select)
		unselect(data);
}

static void	add_back(t_bash *data)
{
	data->is_select = 0;
	arrow_left(data);
	term_put(SAVE);
	ft_putstr(BACK_BLUE);
	ft_putchar(data->vector->line[data->start_select]);
	ft_putstr(RESET);
	term_put(RESET_C);
	data->is_select = SLEFT;
}

void	select_back(t_bash *data)
{
	if (data->iterator)
	{
		if (data->is_select)
		{
			if (data->is_select == SLEFT)
				data->start_select -= 1;
			else
			{
				reset_back(data);
				return ;
			}
		}
		else
		{
			data->end_select = data->iterator;
			data->start_select = data->iterator - 1;
		}
		if (data->start_select < data->end_select)
			add_back(data);
	}
}
