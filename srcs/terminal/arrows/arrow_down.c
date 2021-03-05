/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:04:17 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:36:57 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	arrow_down(t_bash *data)
{
	int				count;

	if (VECT_DOWN || data->history_stack)
	{
		data->history_stack--;
		key_start(data);
		SAVE_C;
		clear_term(data->vector->line);
		RESET_C;
		count = data->history_stack;
		if (!VECT_DOWN)
			while (count-- > 0 && VECT_UP)
				VECT = VECT_UP;
		else
			VECT = VECT_DOWN;
		print_rest(LINE, data->iterator, NULL);
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, ft_strlen(LINE),
			get_win_max_col(), data->prompt_len);
		if (data->cursor)
			data->x = ft_strlen(data->cursor->line);
		if (data->cursor)
			data->y = get_y_cursor(data->cursor);
		data->iterator = ft_strlen(LINE);
	}
}
