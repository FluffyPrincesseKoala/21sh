/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_left_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:39:32 by koala             #+#    #+#             */
/*   Updated: 2020/12/10 15:39:35 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int			move_to_endline(t_bash *data, int prompt_len)
{
	int				count;

	if (data->cursor->prev)
		data->cursor = data->cursor->prev;
	if (data->y <= 1)
		count = prompt_len + data->cursor->line_len;
	else
		count = data->cursor->line_len;
	while (--count)
		RIGHT;
	return (data->cursor->line_len);
}

void				move_left(t_bash *data)
{
	if (data->x || data->y)
	{
		LEFT;
		if (data->x == 0 && data->y)
		{
			UP;
			data->x = move_to_endline(data, data->prompt_len) - 1;
			data->y--;
		}
		else
			data->x--;
		data->iterator--;
	}
}

void				arrow_left(t_bash *data)
{
	if (data->iterator)
	{
		if (data->is_select)
		{
			unselect(data);
			uncolor(data);
		}
		fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
		if (data->cursor)
		{
			data->cursor = find_cursor_node(&data->cursor,	data->iterator,
												get_win_max_col(), data->prompt_len);
			move_left(data);
			clear_struct(&data->cursor);
		}
	}
}

void				move_right(t_bash *data)
{
	if (data->x + 1 == data->cursor->x_max || data->x == data->cursor->line_len
	|| data->cursor->line[data->x] == '\n')
	{
		if (data->cursor->next)
			data->cursor = data->cursor->next;
		data->x = 0;
		data->y++;
		CDOWN;
	}
	else
	{
		data->x++;
		RIGHT;
	}
	data->iterator++;
}

void				arrow_right(t_bash *data)
{
	if (data->iterator < ft_strlen(LINE))
	{
		if (data->is_select)
		{
			unselect(data);
			uncolor(data);
		}
		fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
												get_win_max_col(), data->prompt_len);
		move_right(data);
		clear_struct(&data->cursor);
	}
}