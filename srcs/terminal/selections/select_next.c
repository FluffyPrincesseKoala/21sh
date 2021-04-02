/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:05 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:01:01 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	add_next(t_bash *data)
{
	data->is_select = 0;
	term_put(SAVE);
	ft_putstr(BACK_BLUE);
	ft_putchar(data->vector->line[data->end_select - 1]);
	ft_putstr(RESET);
	term_put(RESET_C);
	arrow_right(data);
	data->is_select = SRIGHT;
}

static void	reset_next(t_bash *data)
{
	term_put(SAVE);
	ft_putchar(data->vector->line[data->start_select]);
	term_put(RESET_C);
	data->start_select += 1;
	data->is_select = 0;
	arrow_right(data);
	data->is_select = SLEFT;
	if (data->end_select == data->start_select)
		unselect(data);
}

void	select_next(t_bash *data)
{
	if (data->iterator < ft_strlen(data->vector->line))
	{
		if (data->is_select)
		{
			if (data->is_select == SRIGHT)
				data->end_select += 1;
			else
			{
				reset_next(data);
				return ;
			}
		}
		else
		{
			data->end_select = data->iterator + 1;
			data->start_select = data->iterator;
		}
		if (data->start_select < data->end_select)
			add_next(data);
	}
}
