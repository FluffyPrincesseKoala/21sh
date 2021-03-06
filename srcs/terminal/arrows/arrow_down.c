/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:04:17 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:16:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	arrow_down(t_bash *data)
{
	int				count;

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
		set_cursors(data, &data->cursor, data->vector->line, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor,
			ft_strlen(data->vector->line), get_win_max_col(), data->prompt_len);
		if (data->cursor)
			data->x = ft_strlen(data->cursor->line);
		if (data->cursor)
			data->y = get_y_cursor(data->cursor);
		data->iterator = ft_strlen(data->vector->line);
	}
}
