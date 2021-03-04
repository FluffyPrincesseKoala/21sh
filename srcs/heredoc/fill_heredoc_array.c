/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:28:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:57:54 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char	**add_to_heredoc_array(t_vect *cmd, char **line)
{
	if (cmd->doc_string)
		cmd->doc_string = array_add_value(cmd->doc_string, *line);
	else
		cmd->doc_string = create_array(*line);
}

void		fill_heredoc_array(t_bash *data, t_vect *cmd, char **line)
{
	char	*new;

	if (line && *line)
	{
		if (ft_strchr(*line, '$'))
		{
			new = use_shell_var(data->env, *line);
			add_to_heredoc_array(cmd, &new);
			ft_strdel(&new);
		}
		else
			add_to_heredoc_array(cmd, line);
	}
}
