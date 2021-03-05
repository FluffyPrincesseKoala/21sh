/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:38:43 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:42:26 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	arrow_up(t_bash *data)
{
	int		count;

	if (VECT_UP)
	{
		data->history_stack++;
		key_start(data);
		SAVE_C;
		clear_term(data->vector->line);
		RESET_C;
		count = data->history_stack;
		if (!VECT_DOWN)
			while (count-- && VECT_UP)
				VECT = VECT_UP;
		else
			VECT = VECT_UP;
		print_rest(LINE, data->iterator, NULL);
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, ft_strlen(LINE),
			get_win_max_col(), data->prompt_len);
		data->x = ft_strlen(data->cursor->line);
		data->y = get_y_cursor(data->cursor);
		data->iterator = ft_strlen(LINE);
	}
}
