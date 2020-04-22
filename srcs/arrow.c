/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/22 19:23:42 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void				arrow_left(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;

	if (data->iterator)
	{
   		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		if (data->iterator + data->prompt_len >= w.ws_col)
		{
			y = (data->iterator + data->prompt_len) / w.ws_col;
			x = (data->iterator + data->prompt_len) % w.ws_col;
			if (!x && y)
			{
				UP;
				data->iterator--;
				while (x++ != w.ws_col)
					RIGHT;
				return ;
			}
		}
		data->iterator--;
		LEFT;
	}
}

void				arrow_right(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;

	if (data->iterator < ft_strlen(data->vector->line))
	{
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		if (data->prompt_len + ft_strlen(data->vector->line) >= w.ws_col)
		{
			y = (data->iterator + data->prompt_len) / w.ws_col;
			x = (data->iterator + data->prompt_len) % w.ws_col;
			if (x == w.ws_col - 1)
			{
				CDOWN;
				data->iterator++;
				return ;
			}
		}
		data->iterator++;
		RIGHT;
	}
}

void				arrow_down(t_bash *data)
{
	if (data->vector->down)
	{
		if (data->iterator)
		{
			data->iterator = 0;
			data->iterator = goto_iterator(*data, data->iterator);
		}
		data->vector = data->vector->down;
		data->iterator = print_rest(data->vector->line, data->iterator,
		(data->vector->up) ? data->vector->up->line : NULL);
		data->iterator = goto_iterator(*data, data->iterator);
	}
}

void				arrow_up(t_bash *data)
{
	if (data->vector->up)
	{
		if (data->iterator)
		{
			data->iterator = 0;
			data->iterator = goto_iterator(*data, data->iterator);
		}
		data->vector = data->vector->up;
		data->iterator = print_rest(data->vector->line, data->iterator,
			(data->vector->down) ? data->vector->down->line : NULL);
		data->iterator = goto_iterator(*data, data->iterator);
	}
}
