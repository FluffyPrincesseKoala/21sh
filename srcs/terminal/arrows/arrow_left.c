/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:56:45 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:37:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	arrow_left(t_bash *data)
{
	if (data->iterator)
	{
		if (data->is_select)
		{
			unselect(data);
			uncolor(data);
		}
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		if (data->cursor)
		{
			data->cursor = find_cursor_node(&data->cursor, data->iterator,
				get_win_max_col(), data->prompt_len);
			move_left(data);
			clear_cursor_struct(&data->cursor);
		}
	}
}
