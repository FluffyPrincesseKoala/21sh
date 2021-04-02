/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:04:17 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:13:22 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	init_position(t_bash *data, t_term *cursor)
{
	data->x = ft_strlen(cursor->line);
	data->y = get_y_cursor(cursor);
}

void	arrow_down(t_bash *data)
{
	int	count;
	int	win_max;

	if (data->vector->down || data->history_stack)
	{
		data->history_stack--;
		key_start(data);
		term_put(SAVE);
		clear_term(data->vector->line);
		term_put(RESET_C);
		count = data->history_stack;
		if (!data->vector->down)
			while (count-- > 0 && data->vector->up)
				data->vector = data->vector->up;
		else
			data->vector = data->vector->down;
		print_rest(data->vector->line, data->iterator, NULL);
		win_max = get_win_max_col();
		set_cursors(data, &data->cursor, data->vector->line, win_max);
		data->cursor = find_cursor_node(&data->cursor,
				ft_strlen(data->vector->line), win_max, data->prompt_len);
		if (data->cursor)
			init_position(data, data->cursor);
		data->iterator = ft_strlen(data->vector->line);
	}
}
