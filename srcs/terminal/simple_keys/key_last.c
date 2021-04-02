/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:24:30 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:58:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	key_last(t_bash *data)
{
	if (data->vector->line)
	{
		set_cursors(data, &data->cursor, data->vector->line, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
				get_win_max_col(), data->prompt_len);
		while (data->iterator < ft_strlen(data->vector->line))
			move_right(data);
		clear_cursor_struct(&data->cursor);
	}
}
