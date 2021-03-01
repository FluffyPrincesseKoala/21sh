/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_content_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:17:06 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/01 19:44:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	merge_last_args(t_bash *data)
{
	t_arg	*new_arg;
	char	*new_content;
	t_arg	*current;

	current = data->vector->args;
	while(current && current->next && current->next->next)
		current = current->next;
	if (current->next)
	{
		new_content = ft_strjoin(current->content, current->next->content);
		if (!(new_arg = create_arg(new_content)))
			data->error = MALLOC_ERROR;
		del_one_arg(current->next, data->vector);
		del_one_arg(current, data->vector);
		add_arg(&data->vector->args, new_arg);
	}
}

void		line_content_to_args(t_bash *data, char *line)
{
	size_t	i;
	char	quote;
	size_t	full_word;

	i = 0;
	full_word = TRUE;
	while (line && line[i] && !data->error)
	{
		if (ft_iswhitespace(line[i]))
		{
			full_word = TRUE;
			i++;
		}
		else
		{
			if (quote = is_quote(line[i]))
				i += create_quoted_arg(data, &line[i], quote);
			else
				i += create_non_quoted_arg(data, &line[i]);
			if (full_word == FALSE)
				merge_last_args(data);
			full_word = FALSE;
		}
	}
}
