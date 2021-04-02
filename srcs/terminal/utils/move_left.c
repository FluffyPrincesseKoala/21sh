/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:55:49 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:56:09 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	move_to_endline(t_bash *data, int prompt_len)
{
	int	count;

	if (data->cursor->prev)
		data->cursor = data->cursor->prev;
	if (data->y <= 1)
		count = prompt_len + data->cursor->line_len;
	else
		count = data->cursor->line_len;
	while (--count)
		term_put(RIGHT);
	return (data->cursor->line_len);
}

void	move_left(t_bash *data)
{
	if (data->x || data->y)
	{
		term_put(LEFT);
		if (data->x == 0 && data->y)
		{
			term_put(UP);
			data->x = move_to_endline(data, data->prompt_len) - 1;
			data->y--;
		}
		else
			data->x--;
		data->iterator--;
	}
}
