/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:13:16 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:13:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ctrl_down(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				expected;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!data->expend)
	{
		init_xy(data, &x, &y, w.ws_col);
		expected = y + 1;
		while (y != expected && data->iterator < ft_strlen(LINE))
		{
			init_xy(data, &x, &y, w.ws_col);
			arrow_right(data);
		}
	}
}
