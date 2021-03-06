/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_suppr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:59:03 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:55:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void				key_suppr(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (data->iterator < ft_strlen(data->vector->line))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		tmp = delchar(data->vector->line, data->iterator);
		expected = data->iterator;
		term_put(SAVE);
		print_rest(NULL, data->iterator, data->vector->line);
		term_put(RESET_C);
		ft_strdel(&data->vector->line);
		data->vector->line = ft_strdup(tmp);
		ft_strdel(&tmp);
		print_rest(data->vector->line, data->iterator, NULL);
		term_put(RESET_C);
	}
}
