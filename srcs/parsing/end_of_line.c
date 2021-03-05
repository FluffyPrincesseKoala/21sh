/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:17:30 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 11:22:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void		update_pending_line(t_bash *data)
{
	if (pending_line(data->vector->line) && !data->expend)
	{
		push_entry(data, "\n", &data->vector->line, data->iterator);
		data->iterator++;
	}
	VECT_UP->line = str_join_free(&VECT_UP->line, &data->vector->line);
	data->vector = VECT_UP;
	free_vector(&VECT_DOWN, FALSE);
	VECT_DOWN = NULL;
	data->y++;
	data->x = 0;
}

static t_vect	*link_history(t_vect **head, t_vect *new)
{
	t_vect	*lst;

	if (head && *head)
	{
		lst = *head;
		lst->down = (new) ? new : vect_new(NULL, NULL);
		lst->down->up = lst;
		if (lst->up)
			lst->up->down = lst;
		lst = lst->down;
		return (lst);
	}
	return (new);
}

static void		new_line(t_bash *data)
{
	error_code_to_message(&(data->error));
	if (LINE)
	{
		VECT = link_history(&VECT, NULL);
	}
	data->iterator = 0;
	data->x = 0;
	data->prompt_len = prompt(data->env, data->expend);
	data->history_stack = 0;
}

int				end_of_line(t_bash **data)
{
	int		exit;

	exit = 0;
	key_last((*data));
	if ((*data)->vector->down)
		pull_line(&(*data)->vector);
	if ((*data)->is_heredoc)
		update_heredoc((*data));
	else if ((*data)->expend)
		update_pending_line((*data));
	else if (is_all_whitespaces((*data)->vector->line))
	{
		ft_putchar('\n');
		ft_strdel(&(*data)->vector->line);
	}
	if ((exit = handle_parsing_execution(*data)) != -1)
		new_line((*data));
	reset_conf_term();
	return (exit);
}
