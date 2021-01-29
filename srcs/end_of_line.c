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
		push_entry(data, "\n", &data->vector->line, ft_strlen(LINE));
		ft_putchar('\n');
	}
	return (data->expend);
}

static void prompt_new_line(t_bash *data)
{
	data->iterator = 0;
	data->x = 0;
	data->prompt_len = prompt(data->env, data->expend);
}

static void new_line(t_bash *data)
{
	error_code_to_message(&(data->error));
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
		push_entry(data, "\n", &data->vector->line, data->iterator++);
	VECT_UP->line = str_join_free(&VECT_UP->line, &LINE);
	VECT = VECT_UP;
	free_vector(&VECT_DOWN, FALSE);
	VECT_DOWN = NULL;
	data->y++;
	data->x = 0;
}

//int			handle_command(t_bash *data, t_vect *command)
//{
//	int exit;
//
//	exit = 0;
//	while (command)
//	{
//		set_up_command_redirections(data, command);
//		if ((exit = check_built_in(data, command)) == 0)
//		{
//			if (!data->error)
//				handle_fork(data, command);
//		}
//		if (exit == -1)
//			return (exit);
//		while (command->separator == '|')
//			command = command->next;
//		command = command->next;
//	}
//	return (exit);
//}

int			handle_parsing_execution(t_bash *data)
{
	int		is_pending;

	is_pending = 0;
	if ((data->vector->line
		|| (data->vector->doc_string && data->vector->separator))
		&& (!(is_pending = is_pending_line(data)))
		|| (is_pending && data->vector->doc_string))
	{
		ft_putchar('\n');
		if (!data->vector->doc_string)
			format_line(data);
		if (!data->is_here_doc)
			return (handle_commands(data, data->vector));
	}
	return (0);
}

int			handle_eol(t_bash **data)
{
	int		exit;

	exit = 0;
	key_last((*data));
	if ((*data)->vector->down)
		pull_line(&(*data)->vector);
	if ((*data)->is_here_doc)
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
