/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncolor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:39:02 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:55:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

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
	term_put(SAVE);
	print_rest(data->vector->line, data->iterator, data->vector->line);
	term_put(RESET_C);
	while (data->iterator != idx)
		arrow_right(data);
}
