/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:17:30 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:18:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	update_pending_line(t_bash *data)
{
	if (pending_line(data->vector->line) && !data->expend)
	{
		push_entry(data, "\n", &data->vector->line, data->iterator);
		data->iterator++;
	}
	data->vector->up->line = str_join_free(&data->vector->up->line,
			&data->vector->line);
	data->vector = data->vector->up;
	free_vector(&data->vector->down, FALSE);
	data->vector->down = NULL;
	data->y++;
	data->x = 0;
}

static t_vect	*link_history(t_vect **head, t_vect *new)
{
	t_vect	*lst;

	if (head && *head)
	{
		lst = *head;
		if (new)
			lst->down = new;
		else
			lst->down = vect_new(NULL, NULL);
		lst->down->up = lst;
		if (lst->up)
			lst->up->down = lst;
		lst = lst->down;
		return (lst);
	}
	return (new);
}

static void	new_line(t_bash *data)
{
	error_code_to_message(&(data->error));
	if (data->vector->line)
		data->vector = link_history(&data->vector, NULL);
	data->iterator = 0;
	data->x = 0;
	data->venv = data->env;
	data->prompt_len = prompt(data->env, data->expend);
	data->history_stack = 0;
}

static void	reset_conf_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_new_term);
}

int	end_of_line(t_bash **data)
{
	int	exit;

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
	exit = handle_parsing_execution(*data);
	if (exit != -1)
		new_line((*data));
	reset_conf_term();
	return (exit);
}
