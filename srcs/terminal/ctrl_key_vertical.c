/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key_vertical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 19:10:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	len_between_last_delim(char *str, char delim, int start)
{
	int				i;

	i = (str[start] == delim) ? 1 : 0;
	while (start - i > 0 && str[start - i] != delim)
		i++;
	return (i);
}

static int  get_curent_line(char *str, int pos, int max, int prompt)
{
	int				i;
	int				y;
	int				len_max;

	i = 0;
	y = 0;
	while (i != pos)
	{
		if (str[i] == '\n')
		{
			if (y)
			{
				y += (ft_strlendelim(str, '\n', i) - i) / max;
			}
			y++;
		}
		i++;
	}
	return (y);
}

void        init_xy(t_bash *data, int *x, int *y, int max)
{
	if (!(*y = get_curent_line(LINE, data->iterator, max, data->prompt_len)))
	{
		*y = (data->iterator + data->prompt_len) / max;
		*x = (data->iterator + data->prompt_len) % max;
	}
	else if (x)
		*x = len_between_last_delim(LINE, '\n', data->iterator);
}
