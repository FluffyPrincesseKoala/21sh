/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_newline_as_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:34:02 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 17:18:18 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	unlink_free_vector(t_vect **to_free, t_vect *new_next)
{
	t_vect	*vect;
	t_vect	*nxt_vect;
	t_arg	*nxt_arg;

	if (to_free && (vect = (*to_free)->next))
	{
		while (vect && vect != new_next)
		{
			nxt_vect = vect->next;
			ft_strdel(&vect->line);
			free_all_args(&vect->args, FALSE);
			free(vect);
			vect = nxt_vect;
		}
		(*to_free)->next = new_next;
		if (!new_next)
			(*to_free)->separator = 0;
	}
}

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/

static int	is_eof(t_bash *data, t_vect *cmd)
{
	int		current;
	

	current = 0;
	while (cmd->doc_string[current])
	{
		if (ft_strequ(cmd->eof, cmd->doc_string[current]))
		{
			data->is_heredoc = data->nb_heredoc - ++data->finish_heredoc;
			return (1);
		}
		current++;
	}
	return (0);
}

static char	*concat_args_in_heredoc(t_arg *arg)
{
	char	*new;
	char	*tmp;
	char	*tmp_nxt;

	new = NULL;
	tmp = NULL;
	tmp_nxt = NULL;
	while (arg)
	{
		if (!new && arg->content)
			new = ft_strdup(arg->content);
		else
		{
			tmp = ft_strjoin(new, " ");
			tmp_nxt = str_join_free(&tmp, &arg->content);
			new = ft_strdup(tmp_nxt);
			ft_strdel(&tmp_nxt);
		}
		arg = arg->next;
	}
	return (new);
}

static int	parse_newline_as_heredoc(t_bash *data, t_vect *cmd, t_vect *next_doc)
{
	char	*new;
	t_vect	*to_free;

	if (cmd->separator == '\n')
	{
		to_free = cmd;
		while (cmd = cmd->next)
		{
			if (new = concat_args_in_heredoc(cmd->args))
			{
				fill_heredoc_array(data, next_doc, &new);
				ft_strdel(&new);
			}
			if (is_eof(data, next_doc))
			{
				unlink_free_vector(&to_free, cmd->next);
				return (-1);
			}
		}
		unlink_free_vector(&to_free, NULL);
	}
	return (0);
}

/*
**	parse lst to:
**	get vect->eof
**	count the number of unfinish heredoc and finish one
**	fill vect->doc_string array if there is some "\n" separator
**	return the first arg to free
*/

t_arg	*set_heredoc(t_bash *data, t_vect **cmd)
{
	t_arg		*arg;
	t_arg		*to_free;
	int			is_doc;

	to_free	= NULL;
	is_doc = 0;
	arg = (*cmd)->args;
	while (arg && is_doc != -1)
	{
		if (is_doc == 1)
		{
			ft_strdel(&(*cmd)->eof);
			if (!arg->content)
				data->error = UNEXPECT_COMMAND_END_ERROR;
			if (!((*cmd)->eof = ft_strdup(arg->content)))
				data->error = MALLOC_ERROR;
			is_doc = parse_newline_as_heredoc(data, *cmd, *cmd);
		}
		if (arg->content && ft_strstr(arg->content, "<<"))
		{
			if (!to_free)
				to_free = arg;
			data->nb_heredoc++;
			data->is_heredoc = 1;
			is_doc = 1;
		}
		arg = arg->next;
	}
	if (!(*cmd)->eof && is_doc)
		data->error = UNEXPECT_COMMAND_END_ERROR;
	return (to_free);
}
