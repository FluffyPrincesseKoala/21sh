/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:05 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:52:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	add_next(t_bash *data)
{
	data->is_select = 0;
	SAVE_C;
	ft_putstr(BACK_BLUE);
	ft_putchar(LINE[data->end_select - 1]);
	ft_putstr(RESET);
	RESET_C;
	arrow_right(data);
	data->is_select = SRIGHT;
}

static void	reset_next(t_bash *data)
{
	SAVE_C;
	ft_putchar(LINE[data->start_select]);
	RESET_C;
	data->start_select += 1;
	data->is_select = 0;
	arrow_right(data);
	data->is_select = SLEFT;
	if (data->end_select == data->start_select)
		unselect(data);
}

void		select_next(t_bash *data)
{
	if (data->iterator < ft_strlen(LINE))
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
