/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:38:43 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/15 20:29:17 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	arrow_up(t_bash *data)
{
	int		count;

	if (data->vector->up)
	{
		data->history_stack++;
		key_start(data);
		term_put(SAVE);
		clear_term(data->vector->line);
		term_put(RESET_C);
		count = data->history_stack;
		if (!data->vector->down)
			while (count-- && data->vector->up)
				data->vector = data->vector->up;
		else
			data->vector = data->vector->up;
		print_rest(data->vector->line, data->iterator, NULL);
		set_cursors(data, &data->cursor, data->vector->line, get_win_max_col());
		if ((data->cursor = find_cursor_node(&data->cursor,
			ft_strlen(data->vector->line), get_win_max_col(), data->prompt_len)))
		{	
			data->x = ft_strlen(data->cursor->line);
			data->y = get_y_cursor(data->cursor);
		}
		data->iterator = ft_strlen(data->vector->line);
	}
}
