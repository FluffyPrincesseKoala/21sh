/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/12 18:17:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			len_between_last_delim(char *str, char delim, int start)
{
	int				i;

	i = (str[start] == delim) ? 1 : 0;
	while (start - i > 0 && str[start - i] != delim)
		i++;
	return (i);
}

int					get_curent_line(char *str, int pos, int max, int prompt)
{
	int				i;
	int				y;
	int				len_max;

	i = 0;
	y = 0;
	while (i != pos)
	{
		if (str[i] == '\n')
		{
			if (y)
			{
				y += (lendelim(str, '\n', i) - i) / max;
			}
			y++;
		}
		i++;
	}
	return (y);
}

void				init_xy(t_bash *data, int *x, int *y, int max)
{
	if (!(*y = get_curent_line(LINE, data->iterator, max, data->prompt_len)))
	{
		*y = (data->iterator + data->prompt_len) / max;
		*x = (data->iterator + data->prompt_len) % max;
	}
	else if (x)
	{
		*x = len_between_last_delim(LINE, '\n', data->iterator);
	}
}

void				move_cursor_to_last_new_line(t_bash *data, int max)
{
	int				x;
	int				y;
	int				last_delim;

	x = 0;
	init_xy(data, NULL, &y, max);
	last_delim = len_between_last_delim(LINE, '\n', data->iterator);
	UP;
	while (last_delim && --last_delim)
		LEFT;
	while (y == 1 && x++ != data->prompt_len)
		RIGHT;
	last_delim = len_between_last_delim(data->vector->line, '\n', --data->iterator);
	while (--last_delim)
		RIGHT;
	if (y == 1)
		RIGHT;
}

void				arrow_left(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;

	if (data->iterator)
	{
   		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		init_xy(data, &x, &y, w.ws_col);
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
		if (data->vector->line[data->iterator - 1] == '\n' && !data->expend)
			move_cursor_to_last_new_line(data, w.ws_col);
		else if (!data->expend || !(data->vector->line[data->iterator - 1] == '\n'))
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

	if (data->iterator < ft_strlen(data->vector->line))
	{
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		init_xy(data, &x, &y, w.ws_col);
		if (data->prompt_len + ft_strlen(data->vector->line) >= w.ws_col
		|| (data->expend && len_between_last_delim(LINE, '\n', data->iterator) >= w.ws_col))
		{
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
		}
		else
		{
			data->iterator++;
			RIGHT;
		}
	}
}

void				arrow_down(t_bash *data) // update me plz :'(
{
	int				len;
	int				count;
	char			*old;

	old = NULL;
	if (VECT_DOWN)
	{
		data->history_stack -= (data->history_stack > 0) ?  1 : 0;
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

/*
**	move curser N time
**	N = diff between end of LINE and curser possition
*/

void	move_n_left(t_bash *data, int num)
{
	struct winsize	w;
	int				y;
	int				x;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) //check return 4 real
		return ;
	y = (num + data->prompt_len) / w.ws_col;
	x = (num + data->prompt_len) % w.ws_col;
	while (num-- != ft_strlen(LINE))
	{
		if (!x && y)
		{
			y--;
			UP;
			while (x++ != w.ws_col)
				RIGHT;
		}
		else
		{
			x--;
			LEFT;
		}
	}
}

static void			lost_cursor(int prompt_len, int line_len)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (prompt_len + line_len == w.ws_col)
		CDOWN;
}

void				arrow_up(t_bash *data)
{
	int		count;
	int		len;
	char	*old;

	old = NULL;
	if (VECT_UP)
	{
		data->history_stack++;
		old = ft_strdup(LINE); // Fédaration départementale des Dormeur Ukrainien Pentoufalart
		key_start(data);
		if (!VECT_DOWN)
		{
			count = data->history_stack;
			while (count-- && VECT_UP)
				VECT = VECT_UP;
		}
		else
			VECT = VECT_UP;
		count = print_rest(LINE, data->iterator, old);
		if (count > (len = ft_strlen(LINE)) && old)
			move_n_left(data, count - data->iterator);
		lost_cursor(data->prompt_len, count);
		data->iterator = len;
		ft_strdel(&old);
	}
}
