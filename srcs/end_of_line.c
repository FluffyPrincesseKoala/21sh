/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:55:45 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/30 16:12:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int  is_pending_line(t_bash *data)
{
	if (data->expend = pending_line(LINE))
	{
		key_last(data);
		push_entry(data, "\n", &data->vector->line, ft_strlen(LINE));
		ft_putchar('\n');
	}
	return (data->expend);
}

static void prompt_new_line(t_bash *data)
{
	data->iterator = 0;
	data->x = 0;
	data->prompt_len = prompt(data->expend);
}

static void new_line(t_bash *data)
{
	if (LINE)
	{
		VECT = link_history(&VECT, NULL);
	}
	prompt_new_line(data);
	data->history_stack = 0;
}

static void update_pending_line(t_bash *data)
{
	if (pending_line(LINE) && !data->expend)
	{
		push_entry(data, "\n", &data->vector->line, data->iterator++);
		ft_putchar('\n');
	}
	VECT_UP->line = str_join_free(&VECT_UP->line, &LINE);
	VECT = VECT_UP;
	free_vector(&VECT_DOWN);
	VECT_DOWN = NULL;
	data->y++;
	data->x = 0;
}

int			handle_eol(t_bash *data, char *buff)
{
	/*
	** GESTION D'ERREUR !!
	*/

	if (data->vector->down)
		pull_line(&data->vector);
	if (data->expend)
		update_pending_line(data);
	else if (is_all_whitespaces(LINE))
	{
		ft_putchar('\n');
		ft_strdel(&LINE);
	}
	if (LINE && !is_pending_line(data))
	{
		info("LAPIN");
		key_last(data);
		format_line(data);
		exec_onebyone(*data);
	}
	new_line(data);
}
