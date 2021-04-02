/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:15:20 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/02 20:24:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	is_pending_line(t_bash *data)
{
	if (!data->is_heredoc)
		data->expend = pending_line(data->vector->line);
	if (data->expend)
	{
		push_entry(data, "\n",
			&data->vector->line, ft_strlen(data->vector->line));
		ft_putchar('\n');
	}
	return (data->expend);
}

static int	format_line_required(t_bash *data)
{
	if ((!data->vector->doc_string && !data->finish_heredoc)
		|| !data->vector->args)
		return (TRUE);
	return (FALSE);
}

int	handle_parsing_execution(t_bash *data)
{
	int		is_pending;

	if ((data->vector->line
			|| (data->vector->doc_string && data->vector->separator)))
	{
		is_pending = is_pending_line(data);
		if ((!is_pending) || (is_pending && data->vector->doc_string))
		{
			ft_putchar('\n');
			if (format_line_required(data))
				format_line(data);
			if (!data->is_heredoc && !data->error
				&& data->vector->args->content)
				return (handle_commands(data, data->vector));
		}
	}
	return (0);
}
