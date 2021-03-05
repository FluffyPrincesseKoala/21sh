/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:28:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 18:08:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char	**create_array(char *first)
{
	char	**ret;

	if (!(ret = malloc(sizeof(char *) * (2))))
		return (NULL);
	ret[0] = ft_strdup(first);
	ret[1] = NULL;
	return (ret);
}

static char	**add_to_heredoc_array(t_vect *cmd, char **line)
{
	if (cmd->doc_string)
		cmd->doc_string = add_value_to_array(cmd->doc_string, *line);
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
