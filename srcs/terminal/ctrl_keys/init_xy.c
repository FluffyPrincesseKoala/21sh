/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:03:42 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	len_between_last_delim(char *str, char delim, int start)
{
	int				i;

	if (str[start] == delim)
		i = 1;
	else
		i = 0;
	while (start - i > 0 && str[start - i] != delim)
		i++;
	return (i);
}

static int	get_curent_line(char *str, int pos, int max, int prompt)
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

void	init_xy(t_bash *data, int *x, int *y, int max)
{
	*y = get_curent_line(data->vector->line, data->iterator,
			max, data->prompt_len);
	if (!(*y))
	{
		*y = (data->iterator + data->prompt_len) / max;
		*x = (data->iterator + data->prompt_len) % max;
	}
	else if (x)
		*x = len_between_last_delim(data->vector->line, '\n', data->iterator);
}
