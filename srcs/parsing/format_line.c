/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:50:02 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:48:19 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	detach_args(t_vect *current, t_arg *last_arg_before_doomsday)
{
	if (last_arg_before_doomsday->next)
	{
		current->next = vect_new(last_arg_before_doomsday->next, NULL);
		last_arg_before_doomsday->next->previous = NULL;
		last_arg_before_doomsday->next = NULL;
	}
}

static void	get_post_separator_args(
	t_bash *data, t_vect *cmd, t_arg *arg, int index)
{
	char			*substring;
	t_arg			*new;
	unsigned int	len;

	substring = NULL;
	new = NULL;
	len = ft_strlen(arg->content);
	substring = ft_strsub(arg->content, index, len - index);
	if (substring)
	{
		if (insert_new_arg(cmd, arg, substring))
			return ;
		ft_strdel(&substring);
	}
	data->error = MALLOC_ERROR;
}

static int	is_heredoc(t_bash *data)
{
	if (!data->vector->doc_string)
		if (ft_strstr(data->vector->line, "<<"))
			return (TRUE);
	return (FALSE);
}

void	format_line(t_bash *data)
{
	t_vect	*loop;
	char	**table;
	char	*tmp;

	tmp = ft_replace_substr(data->vector->line, "\n", " \n");
	if (tmp)
	{
		table = ft_strsplit(tmp, ' ');
		if (ft_arraylen(table))
			line_content_to_args(data, data->vector->line);
	}
	if (!data->vector->args || data->error)
		error_code_to_message(&data->error);
	else if (is_heredoc(data))
		heredoc(data);
	free_array(table);
	ft_strdel(&tmp);
}
