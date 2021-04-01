/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:42:18 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/26 21:50:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void		return_exit(t_bash *data)
{
	if (!data->vector->line && data->expend)
	{
		g_data->x = 0;
		g_data->y = 0;
		if (data->is_heredoc)
		{
			data->is_heredoc = 0;
			end_of_line(&data);
			return ;
		}
		data->expend = 0;
		term_put(DOWN);
		ft_putstr(tgetstr("cr", NULL));
		prompt(g_data->env, 0);
	}
	else if (!data->vector->line || !ft_strlen(data->vector->line))
	{
		ft_putendl("exit");
		unconf_term();
		free_bash(data);
		exit(0);
	}
	else
		return ;
}
