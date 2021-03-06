/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:25:25 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:55:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	key_back(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (data->iterator && ft_strlen(data->vector->line))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		tmp = delchar(data->vector->line, data->iterator - 1);
		expected = data->iterator - 1;
		arrow_left(data);
		old = ft_strdup(data->vector->line);
		ft_strdel(&data->vector->line);
		data->vector->line = ft_strdup(tmp);
		term_put(SAVE);
		print_rest(NULL, data->iterator, old);
		term_put(RESET_C);
		print_rest(data->vector->line, data->iterator, NULL);
		term_put(RESET_C);
		ft_strdel(&old);
		ft_strdel(&tmp);
	}
}
