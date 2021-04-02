/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:58:01 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:06:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	arrow_right(t_bash *data)
{
	if (data->iterator < ft_strlen(data->vector->line))
	{
		if (data->is_select)
		{
			unselect(data);
			uncolor(data);
		}
		set_cursors(data, &data->cursor, data->vector->line, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
				get_win_max_col(), data->prompt_len);
		move_right(data);
		clear_cursor_struct(&data->cursor);
	}
}
