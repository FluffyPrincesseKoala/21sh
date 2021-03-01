/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:34:48 by koala             #+#    #+#             */
/*   Updated: 2021/03/01 19:43:58 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	format_line_required(t_bash *data)
{
	if ((!data->vector->doc_string && !data->finish_heredoc)
		|| !data->vector->args)
		return (TRUE);
	return (FALSE);
}

int	is_exit(t_vect *command)
{
	if (ft_strequ(command->args->content, "exit"))
		return (TRUE);
	return (FALSE);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	else
		return (0);
}