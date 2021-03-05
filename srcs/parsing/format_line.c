/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:50:02 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 19:40:21 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
	len = ft_strlen(CONTENT);
	if (substring = ft_strsub(arg->content, index, len - index))
	{
		if (insert_new_arg(cmd, arg, substring))
			return ;
		ft_strdel(&substring);
	}
	data->error = MALLOC_ERROR;
}

static int	is_heredoc(t_bash *data)
{
	t_vect	*current;
	t_arg	*args;

	if (!data->vector->doc_string && (current = data->vector))
	{
		if (ft_strstr(data->vector->line, "<<"))
		{
			while (current && (args = current->args))
			{
				while (args)
				{
					if (ft_strequ(args->content, "<<"))
						return (TRUE);
					args = args->next;
				}
				current = current->next;
			}
		}
	}
	return (FALSE);
}

void		format_line(t_bash *data)
{
	t_vect	*loop;
	char	**table;
	char	*tmp;

	if ((tmp = ft_replace_substr(LINE, "\n", " \n")))
	{
		if (ft_arraylen(table = ft_strsplit(tmp, ' ')))
			line_content_to_args(data, LINE);
	}
	if (!VECT->args || data->error)
		puterror(data->error);
	else if (is_heredoc(data))
		heredoc(data);
	free_array(table);
	ft_strdel(&tmp);
}
