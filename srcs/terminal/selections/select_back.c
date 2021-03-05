/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:32:59 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:53:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	reset_back(t_bash *data)
{
	data->end_select -= 1;
	data->is_select = 0;
	arrow_left(data);
	SAVE_C;
	ft_putchar(LINE[data->end_select]);
	RESET_C;
	data->is_select = SRIGHT;
	if (data->end_select == data->start_select)
		unselect(data);
}

static void	add_back(t_bash *data)
{
	data->is_select = 0;
	arrow_left(data);
	SAVE_C;
	ft_putstr(BACK_BLUE);
	ft_putchar(LINE[data->start_select]);
	ft_putstr(RESET);
	RESET_C;
	data->is_select = SLEFT;
}

void		select_back(t_bash *data)
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
