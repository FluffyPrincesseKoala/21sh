/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:34:02 by koala             #+#    #+#             */
/*   Updated: 2021/03/01 19:11:42 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	unlink_free_vector(t_vect **head, t_vect *new_next)
{
	t_vect	*lst;
	t_vect	*nxt_lst;
	t_arg	*nxt_arg;

	if (head && (lst = (*head)->next))
	{
		while (lst && lst != new_next)
		{
			nxt_lst = lst->next;
			ft_strdel(&lst->line);
			while (lst->args)
			{
				nxt_arg = lst->args->next;
				ft_strdel(&lst->args->content);
				lst->args->content = NULL;
				lst->args->previous = NULL;
				free(lst->args);
				lst->args = nxt_arg;
			}
			free(lst);
			lst = nxt_lst;
		}
		(*head)->next = new_next;
		if (!new_next)
			(*head)->separator = 0;
	}
}

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/

static int	is_eof(t_bash *data, t_vect *cmd) // add t_vect
{
	int		current;
	

	current = 0;
	while (cmd->doc_string[current])
	{
		if (ft_strequ(cmd->eof, cmd->doc_string[current]))
		{
			data->is_here_doc = data->nb_heredoc - ++data->finish_heredoc;
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

static int	create_heredoc_from_next_vector(t_bash *data, t_vect *vect, t_vect *next_doc)
{
	char	*new;
	t_vect	*to_free;

	to_free = vect;
	while ((vect = vect->next))
	{
		if ((new = concat_args_in_heredoc(vect->args)))
		{
			fill_heredoc_array(data, next_doc, &new);
			ft_strdel(&new);
		}
		if (is_eof(data, next_doc))
		{
			next_doc = vect->next;
			unlink_free_vector(&to_free, (next_doc) ? next_doc : NULL);
			return (-1);
		}
	}
	unlink_free_vector(&to_free, NULL);
	return (0);
}

int			parse_newline_as_heredoc(t_vect **head, t_bash *data)
{
	t_vect	*vect;
	t_vect	*vect_to_free;
	char	*new;
	int		is_eof;

	new = NULL;
	is_eof = 0;
	if (head && *head)
		vect = *head;
	while (vect)
	{
		if (vect->separator == '\n')
			is_eof = create_heredoc_from_next_vector(data, vect, *head);
		vect = (vect) ? vect->next : NULL;
	}
	return (is_eof);
}