/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncolor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:39:02 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 17:06:57 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	uncolor(t_bash *data)
{
	int	idx;
	int	count;
	int	x;
	int	y;

	idx = data->iterator;
	x = data->x;
	y = data->y;
	while (data->iterator)
		arrow_left(data);
	SAVE_C;
	print_rest(LINE, data->iterator, LINE);
	RESET_C;
	while (data->iterator != idx)
		arrow_right(data);
}
