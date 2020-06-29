/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:55:45 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/28 14:47:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int  is_pending_line(t_bash *data)
{
	return (data->expend = pending_line(LINE));
}

static void prompt_new_line(t_bash *data)
{
	ft_putchar('\n');
	data->iterator = 0;
	data->prompt_len = prompt(data->expend);
}

static void new_line(t_bash *data)
{
	if (LINE)
	{
		VECT = link_history(&VECT, NULL);
	}
	prompt_new_line(data);
}

static int  is_all_whitespaces(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void update_pending_line(t_bash *data)
{
	VECT_UP->line = str_join_free(&VECT_UP->line, &LINE);
	VECT = VECT_UP;
	free_vector(&VECT_DOWN);
	VECT_DOWN = NULL;
}

int			handle_eol(t_bash *data, char *buff)
{
	/*
	** GESTION D'ERREUR !!
	*/

	if (data->expend)
		update_pending_line(data);  // concat previous and current line
	else if (is_all_whitespaces(LINE))
		ft_strdel(&LINE);
	if (LINE && !is_pending_line(data)) 
	{
		ft_putchar('\n');
		format_line(data);
		search_redirections_in_cmd(data, VECT);
		if (!data->error)
			handle_fork(data, VECT);
	}
	new_line(data);
}
