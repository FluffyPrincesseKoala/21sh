/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:50:02 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 18:59:23 by cylemair         ###   ########.fr       */
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

static void	parse_args(t_bash *data, t_vect *current)
{
	t_arg			*arg;
	unsigned int	i;
	unsigned int	len;
	unsigned int	separator_idx;

	i = 0;
	len = 0;
	separator_idx = 0;
	arg = current->args;
	while (arg)
	{
		if ((separator_idx = arg->separator) != -1)
		{
			current->separator = CONTENT[separator_idx];
			if ((len = ft_strlen(CONTENT)) != separator_idx + 1)
				get_post_separator_args(data, current, arg, separator_idx + 1);
			detach_args(current, arg);
			CONTENT = ft_strsub_free(&CONTENT, 0, separator_idx);
		}
		arg = arg->next;
	}
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
	if (VECT->args && !data->error)
	{
		loop = VECT;
		while (loop)
		{
			parse_args(data, loop);
			loop = loop->next;
		}
	}
	else
		put_error_code(data->error);
	if (is_heredoc(data))
		heredoc(data);
	free_array(table);
	ft_strdel(&tmp);
}
