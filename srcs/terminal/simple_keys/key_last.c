/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:24:30 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:59:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	key_last(t_bash *data)
{
	if (LINE)
	{
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
			get_win_max_col(), data->prompt_len);
		while (data->iterator < ft_strlen(LINE))
			move_right(data);
		clear_cursor_struct(&data->cursor);
	}
}
