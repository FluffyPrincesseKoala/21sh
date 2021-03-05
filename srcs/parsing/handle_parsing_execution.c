/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:15:20 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 11:27:53 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	is_pending_line(t_bash *data)
{
	if (data->expend = pending_line(LINE))
	{
		push_entry(data, "\n", &data->vector->line, ft_strlen(LINE));
		ft_putchar('\n');
	}
	return (data->expend);
}

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
		if (format_line_required(data))
			format_line(data);
		if (!data->is_heredoc && !data->error && data->vector->args->content)
			return (handle_commands(data, data->vector));
	}
	return (0);
}
