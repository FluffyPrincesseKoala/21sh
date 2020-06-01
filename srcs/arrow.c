/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/01 12:42:58 by cylemair         ###   ########.fr       */
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

int			get_curent_line(char *str, int pos)
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
		if (!data->expend && !get_curent_line(LINE, data->iterator))
		{
			y = (data->iterator + data->prompt_len) / w.ws_col;
			x = (data->iterator + data->prompt_len) % w.ws_col;
		}
		else
		{
			y = get_curent_line(LINE, data->iterator);
			x = len_between_last_delim(LINE, '\n', data->iterator);
		}
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
		{
			x = 0;
			y = get_curent_line(data->vector->line, data->iterator);
			
			int last_delim = len_between_last_delim(data->vector->line, '\n', data->iterator);
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

	int sodomite = ft_strlen(data->vector->line);
	if (data->iterator < ft_strlen(data->vector->line))
	{
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		if (data->prompt_len + ft_strlen(data->vector->line) >= w.ws_col
		|| (data->expend
		&& len_between_last_delim(LINE, '\n', data->iterator) >= w.ws_col))
		{
			if (!get_curent_line(LINE, data->iterator))
			{
				y = (data->iterator + data->prompt_len) / w.ws_col;
				x = (data->iterator + data->prompt_len) % w.ws_col;
			}
			else
			{
				x = len_between_last_delim(LINE, '\n', data->iterator);
				y = get_curent_line(LINE, data->iterator);
			}
			if (x == w.ws_col - 1)
			{
				CDOWN;
				data->iterator++;
				return ;
			}
		}
		if (data->vector->line[data->iterator] == '\n' && !data->expend)
		{
			data->iterator++;
			CDOWN;
			if (data->expend)
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
	char			*clean_line;
	char			*tmp;
	int				len;
	int				delim_len;

	if (data->expend && !data->expend_up)
	{
		data->expend_up = 1;
		len = ft_strlen(LINE) - (delim_len = len_between_last_delim(LINE, '\n', data->iterator));
		clean_line = ft_strndup(LINE, len + 1);
		if ((tmp = ft_strjoin(clean_line, ft_strndup(LINE, len))))
		{
			len = ft_strlen(clean_line);
			ft_strdel(&data->vector->line);
			ft_strdel(&clean_line);
			LINE = tmp;
		}
		while (--delim_len)
			arrow_left(data);
		data->iterator = print_rest(LINE, len, NULL);
		delim_len = len_between_last_delim(LINE, '\n', data->iterator - 1);
	}
	else if (data->vector->up)
	{
		if (!data->expend)
		{
			if (data->iterator)
				key_start(data);
			data->vector = data->vector->up;
			data->iterator = print_rest(data->vector->line, data->iterator,
				(data->vector->down) ? data->vector->down->line : NULL);
			key_start(data);
			SAVE_C;
			data->iterator = print_rest(data->vector->line, data->iterator,
				(data->vector->down) ? data->vector->down->line : NULL);
			RESET_C;
			len = data->iterator;
			data->iterator = 0;
			while (len--)
				arrow_right(data);
		}
		else
		{
			len = ft_strlen(LINE)
				- (delim_len = len_between_last_delim(LINE, '\n', data->iterator));
			clean_line = ft_strndup(LINE, len + 1);

			t_vect *upvector = data->vector->up;
			int count = data->expend_up;
			while (--count && upvector->up)
				upvector = upvector->up;

			if (!count)
			{
				if (data->iterator)
					key_start(data);
				if ((tmp = ft_strjoin(clean_line, upvector->line)))
				{
					ft_strdel(&clean_line);
					clean_line = ft_strdup(LINE); // pass old LINE into clean_line
					ft_strdel(&LINE);
					LINE = tmp;
				}
				data->iterator = print_rest(LINE, data->iterator, clean_line);
				data->expend_up++;
			}
			ft_strdel(&clean_line);
		}
	}
}
