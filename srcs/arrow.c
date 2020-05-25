/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/05/22 19:43:39 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int			len_between_last_delim(char *str, char delim, int start)
{
	int				i;

	i = (str[start] == delim) ? 1 : 0;
	while (start - i > 0 && str[start - i] != delim)
		i++;
	return (i);
}

static int			get_curent_line(char *str, int pos)
{
	int				i;
	int				y;

	i = 0;
	y = 0;
	while (i != pos)
	{
		if (str[i] == '\n')
			y++;
		i++;
	}
	return (y);
}

void				arrow_left(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;

	if (data->iterator)
	{
   		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		y = (data->iterator + data->prompt_len) / w.ws_col;
		x = (data->iterator + data->prompt_len) % w.ws_col;
		if (data->iterator + data->prompt_len >= w.ws_col)
		{
			if (!x && y)
			{
				UP;
				data->iterator--;
				while (x++ != w.ws_col)
					RIGHT;
				return ;
			}
		}
		if (data->vector->line[data->iterator - 1] == '\n')
		{
			x = 0;
			y = get_curent_line(data->vector->line, data->iterator);
			
			int last_delim = len_between_last_delim(data->vector->line, '\n', data->iterator);
			UP;
			while (last_delim--)
				LEFT;
			
			while (y == 1 && x++ != data->prompt_len)
				RIGHT;

			last_delim = len_between_last_delim(data->vector->line, '\n', --data->iterator);
			while (last_delim--)
				RIGHT;
		}
		else
		{
			data->iterator--;
			LEFT;
		}
	}
}

void				arrow_right(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;

	int sodomite = ft_strlen(data->vector->line);
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
		if (data->vector->line[data->iterator] == '\n')
		{
			data->iterator++;
			CDOWN;
			if (data->enclose)
				RIGHT;
		}
		else
		{
			data->iterator++;
			RIGHT;
		}
	}
}

void				arrow_down(t_bash *data)
{
	int				len;

	if (data->vector->down)
	{
		if (data->iterator)
			key_start(data);
		SAVE_C;
		data->vector = data->vector->down;
		data->iterator = print_rest(data->vector->line, data->iterator,
		(data->vector->up) ? data->vector->up->line : NULL);
		RESET_C;
		len = data->iterator;
		data->iterator = 0;
		while (len--)
			arrow_right(data);
	}
}

void				arrow_up(t_bash *data)
{
	int				len;

	if (data->vector->up)
	{
		if (data->iterator)
			key_start(data);
		SAVE_C;
		data->vector = data->vector->up;
		data->iterator = print_rest(data->vector->line, data->iterator,
			(data->vector->down) ? data->vector->down->line : NULL);
		RESET_C;
		len = data->iterator;
		data->iterator = 0;
		while (len--)
		{
			if (data->vector->line[data->iterator] == '\n')
			{
				CDOWN;
				data->iterator++;
			}
			else
				arrow_right(data);
		}
	}
}
