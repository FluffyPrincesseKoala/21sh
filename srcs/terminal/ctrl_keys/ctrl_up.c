/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:13:36 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:50:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ctrl_up(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				expected;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	init_xy(data, &x, &y, w.ws_col);
	if (y && !data->expend)
	{
		expected = y - 1;
		while (y != expected)
		{
			init_xy(data, &x, &y, w.ws_col);
			arrow_left(data);
		}
	}
}
