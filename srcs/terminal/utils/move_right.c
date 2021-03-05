/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:57:29 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 14:57:40 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void				move_right(t_bash *data)
{
	if (data->x + 1 == data->cursor->x_max || data->x == data->cursor->line_len
	|| data->cursor->line[data->x] == '\n')
	{
		if (data->cursor->next)
			data->cursor = data->cursor->next;
		data->x = 0;
		data->y++;
		CDOWN;
	}
	else
	{
		data->x++;
		RIGHT;
	}
	data->iterator++;
}
