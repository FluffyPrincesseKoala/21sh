/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:24:56 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:59:41 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	key_start(t_bash *data)
{
	int				prompt_len;

	if (data->iterator)
	{
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
			get_win_max_col(), data->prompt_len);
		while (IDX && (data->x || data->y))
			move_left(data);
		clear_cursor_struct(&data->cursor);
	}
}
