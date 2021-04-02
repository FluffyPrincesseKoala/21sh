/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:57:29 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:55:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	move_right(t_bash *data)
{
	if (data->cursor && data->cursor->line
		&& (data->x + 1 == data->cursor->x_max
			|| data->x == data->cursor->line_len
			|| (data->x > ft_strlen(data->cursor->line)
				|| data->cursor->line[data->x] == '\n')))
	{
		if (data->cursor->next)
			data->cursor = data->cursor->next;
		data->x = 0;
		data->y++;
		term_put(DOWN);
	}
	else
	{
		data->x++;
		term_put(RIGHT);
	}
	data->iterator++;
}
