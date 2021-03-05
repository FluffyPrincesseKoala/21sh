/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:58:01 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:37:24 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	arrow_right(t_bash *data)
{
	if (data->iterator < ft_strlen(LINE))
	{
		if (data->is_select)
		{
			unselect(data);
			uncolor(data);
		}
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
			get_win_max_col(), data->prompt_len);
		move_right(data);
		clear_cursor_struct(&data->cursor);
	}
}
