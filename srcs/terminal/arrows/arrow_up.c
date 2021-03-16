/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:38:43 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/16 13:26:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static t_vect	*go_back(t_bash *data)
{
	t_vect	*cmd;
	int		count;

	cmd = data->vector;
	count = data->history_stack;
	if (!cmd->down)
		while (count-- && cmd->up)
			cmd = cmd->up;
	else
		cmd = cmd->up;
	return (cmd);
}

void			arrow_up(t_bash *data)
{
	if (data->vector->up)
	{
		data->history_stack++;
		key_start(data);
		term_put(SAVE);
		clear_term(data->vector->line);
		term_put(RESET_C);
		go_back(data);
		print_rest(data->vector->line, data->iterator, NULL);
		set_cursors(data, &data->cursor,
			data->vector->line, get_win_max_col());
		if ((data->cursor = find_cursor_node(&data->cursor,
		ft_strlen(data->vector->line), get_win_max_col(), data->prompt_len)))
		{
			data->x = ft_strlen(data->cursor->line);
			data->y = get_y_cursor(data->cursor);
		}
		data->iterator = ft_strlen(data->vector->line);
	}
}
