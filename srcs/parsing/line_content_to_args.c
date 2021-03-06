/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_content_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:17:06 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 17:11:07 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static t_vect	*vect_add(t_vect **head, t_vect *new)
{
	t_vect	*tmp;

	if (head)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*head);
}

static void		merge_last_args(t_bash *data)
{
	t_arg	*new_arg;
	char	*new_content;
	t_arg	*current;

	current = data->vector->args;
	while (current && current->next && current->next->next)
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

static int		word_to_arg(
	t_bash *data, t_vect **current, char *word, size_t *full_word)
{
	char	quote;
	size_t	len;

	len = 1;
	if (((*current)->separator = is_separator(word[0])))
	{
		setup_command_redirections(data, *current);
		*current = vect_new(NULL, NULL);
		vect_add(&data->vector, *current);
		*full_word = TRUE;
	}
	else if (ft_iswhitespace(word[0]))
		*full_word = TRUE;
	else
	{
		if (quote = is_quote(word[0]))
			len = create_quoted_arg(data, *current, word, quote);
		else
			len = create_non_quoted_arg(data, *current, word);
		if (*full_word == FALSE)
			merge_last_args(data);
		*full_word = FALSE;
	}
	return (len);
}

void			line_content_to_args(t_bash *data, char *line)
{
	size_t	i;
	size_t	full_word;
	t_vect	*current;

	i = 0;
	full_word = TRUE;
	current = data->vector;
	while (line && line[i] && !data->error)
	{
		i += word_to_arg(data, &current, line + i, &full_word);
	}
	if (!data->error)
		setup_command_redirections(data, current);
}
