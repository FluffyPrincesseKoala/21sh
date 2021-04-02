/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_content_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:17:06 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/02 20:09:04 by cylemair         ###   ########.fr       */
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

static void	merge_last_args(t_bash *data, t_vect **current)
{
	t_arg	*new_arg;
	char	*new_content;
	char	*new_quoted;
	t_arg	*args;

	args = get_arg_befor_last(current);
	if (args->next)
	{
		new_content = ft_strjoin(args->content, args->next->content);
		if (args->next->quoted)
		{
			if (args->quoted)
				new_quoted = ft_strjoin(args->quoted, args->next->quoted);
			else
				new_quoted = ft_strjoin(args->content, args->next->quoted);
		}
		else
			new_quoted = ft_strjoin(args->quoted, args->next->content);
		new_arg = create_arg(new_content, new_quoted);
		if (!new_arg)
			data->error = MALLOC_ERROR;
		del_one_arg(args->next, *current);
		del_one_arg(args, *current);
		add_arg(&(*current)->args, new_arg);
	}
}

static int	word_to_arg(t_bash *data, t_vect **current, char *word,
						size_t *full_word)
{
	size_t	len;
	char	quote;

	len = 1;
	(*current)->separator = is_separator(word[0]);
	if (ft_iswhitespace(word[0]) || (*current)->separator)
		*full_word = TRUE;
	if ((*current)->separator)
	{
		setup_command_redirections(data, *current);
		*current = vect_new(NULL, NULL);
		vect_add(&data->vector, *current);
	}
	if (!ft_iswhitespace(word[0]))
	{
		quote = is_quote(word[0]);
		if (quote)
			len = create_quoted_arg(data, *current, word, quote);
		else
			len = create_non_quoted_arg(data, *current, word);
		if (*full_word == FALSE)
			merge_last_args(data, current);
		*full_word = FALSE;
	}
	return (len);
}

void	line_content_to_args(t_bash *data, char *line)
{
	size_t	i;
	size_t	full_word;
	t_vect	*current;

	i = 0;
	full_word = TRUE;
	current = data->vector;
	while (line && line[i] && !data->error)
		i += word_to_arg(data, &current, line + i, &full_word);
	if (!data->error)
		setup_command_redirections(data, current);
}
