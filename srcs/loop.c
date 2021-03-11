/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:56:55 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/11 18:25:51 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	handle_new_entry(t_bash *data, char *entry, int pos)
{
	if (!data->vector->line)
		data->vector->line = ft_strndup(entry, 1);
	else
	{
		if (data->vector->down)
			pull_line(&data->vector);
		push_entry(data, entry, &data->vector->line, data->iterator);
	}
	term_put(SAVE);
	data->iterator = pos;
	print_rest(data->vector->line, pos, NULL);
	term_put(RESET_C);
	arrow_right(data);
	return (data->iterator);
}

void		loop(t_bash *data)
{
	char	buff[MAX_INPUT_SIZE];
	int		is_key;
	int		exit;

	is_key = 0;
	exit = 0;
	data->start_expend = 0;
	data->expend_up = 0;
	setup_signals();
	while (42 && exit != -1)
	{
		read(0, buff, MAX_INPUT_SIZE);
		if (ft_strnequ(buff, "\n", 1))
			exit = end_of_line(&data);
		else if (!data->error && (ft_strnequ(buff, "\033", 1)
			|| !ft_isprint(buff[0]) || ft_strnequ(buff, "\f", 1)))
			termi(data, buff);
		else if (!data->error && ft_isprint(buff[0])
			&& !ft_strnequ(buff, "\n", 1))
			data->iterator = handle_new_entry(data, buff, data->iterator);
	}
}
