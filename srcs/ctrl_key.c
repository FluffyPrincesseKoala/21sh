/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:21:14 by cylemair          #+#    #+#             */
/*   Updated: 2020/12/10 15:43:49 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void			init_xy(t_bash *data, int *x, int *y, int max)
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

void				ctrl_right(t_bash *data)
{
	t_term			*curr;
	int				len;

	if (data->iterator < (len = ft_strlen(LINE)))
	{
		while (data->iterator < len && ft_iswhitespace(LINE[data->iterator]))
			arrow_right(data);
		while (data->iterator < len && !ft_iswhitespace(LINE[data->iterator]))
			arrow_right(data);
	}
}

void				ctrl_left(t_bash *data)
{
	t_term			*curr;
	int				len;

	if (data->iterator)
	{
		while (data->iterator && ft_iswhitespace(LINE[data->iterator]))
			arrow_left(data);
		while (data->iterator && !ft_iswhitespace(LINE[data->iterator]))
			arrow_left(data);
	}
}

void				ctrl_down(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				expected;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!data->expend)
	{
		init_xy(data, &x, &y, w.ws_col);
		expected = y + 1;
		while (y != expected && data->iterator < ft_strlen(LINE))
		{
			init_xy(data, &x, &y, w.ws_col);
			arrow_right(data);
		}
	}
}

void				ctrl_up(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				expected;


	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	init_xy(data, &x, &y, w.ws_col);
	if (y && !data->expend)
	{
		expected = y - 1;
		while (y != expected)
		{
			init_xy(data, &x, &y, w.ws_col);
			arrow_left(data);
		}
	}
}
