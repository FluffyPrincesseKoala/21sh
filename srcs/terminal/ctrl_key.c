/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:21:14 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 17:04:23 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
