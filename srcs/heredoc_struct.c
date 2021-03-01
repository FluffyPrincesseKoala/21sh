/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 19:45:12 by koala             #+#    #+#             */
/*   Updated: 2021/03/01 18:20:56 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_heredoc		*create_heredoc(char **doc_string, char *eof)
{
	t_heredoc	*new;

	if (!(new = ft_memalloc(sizeof(t_heredoc))))
		return (NULL);
	new->doc_strings = (doc_string) ? copy_env(doc_string) : NULL;
	new->eof = (eof) ? create_array(eof) : NULL;
	new->eof_idx = 0;
	new->finish_heredoc = 0;
	new->nb_heredoc = 0;
	return (new);
}

/*
**	set* finish_heredoc nb_heredoc eof_idx
*/

void			set_finish_heredoc(t_heredoc **here, int finish)
{
	(*here)->finish_heredoc = finish;
}

void			set_nb_heredoc(t_heredoc **here, int nb)
{
	(*here)->nb_heredoc = nb;
}

void			set_eof_idx(t_heredoc **here, int nb)
{
	(*here)->eof_idx = nb;
}

static char		**merge_array(char **a, char **b)
{
	char		**new;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char*) * (ft_arraylen(a) + ft_arraylen(b) + 1))))
		return (NULL);
	while (a && a[i])
	{
		new[j] = ft_strdup(a[i]);
		j++;
		i++;
	}
	i = 0;
	while (b && b[i])
	{
		new[j] = ft_strdup(b[i]);
		j++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

void			add_eof(t_heredoc **here, char *eof)
{
	char		**new;

	new = copy_env((*here)->eof);
	new = array_add_value(new, eof);
	free_array((*here)->eof);
	(*here)->eof = new;
}

int				is_heredoc_finish(t_heredoc *here)
{
	int			i;
	int			eof_idx;
	int			count;
	int			eof_max;

	i = 0;
	eof_idx = here->eof_idx;
	count = here->finish_heredoc;
	eof_max = ft_arraylen(here->eof);
	while (here->doc_strings[i] && eof_idx != eof_max
		&& count != here->nb_heredoc)
	{
		if (ft_strequ(here->doc_strings[i], here->eof[eof_idx]))
		{
			count++;
			eof_idx++;
		}
		i++;
	}
	here->finish_heredoc = count;
	here->eof_idx = eof_idx;
	return (here->finish_heredoc == here->nb_heredoc);
}

void			parse_heredoc_line(t_bash *data)
{
	t_heredoc	*doc;
	t_arg		*arguments;
	t_arg		*to_free;
	t_vect		*vect;
	int			count;

	to_free = NULL;
	count = 0;
	if ((vect = data->vector))
	{
		while (vect && (arguments = vect->args) && !data->error)
		{
			if ((to_free = setup_heredoc(data, &vect, arguments)))
			{
				count++;
				if (!to_free->previous)
					if (!format_heredoc(&vect, &to_free))
					{
						data->error = SNTX_ERR;
						to_free = reset_data_heredoc(data, vect->here);
						return ;
					}
					else
						to_free = set_heredoc(data, &vect,vect->args);
				if (!data->error && to_free)
					free_args_until_eof(vect, &to_free);
			}
		}
	}
	if (!data->error)
	{
		data->nb_heredoc = count; //vect->here->nb_heredoc now
		data->expend = (data->is_here_doc) ? -1 : 0;
	}
}

t_arg		*setup_heredoc(t_bash *data, t_vect **vect, t_arg *lst)
{
	t_arg	*to_free;
	int		is_doc;

	to_free = NULL;
	is_doc = 0;
	while (lst && lst->content && is_doc != -1)
	{
		if (is_doc && lst->previous && ft_strequ(lst->previous->content, "<<"))
		{
			if (!((*vect)->here->eof = create_heredoc(NULL, lst->content)))
				data->error = UNEXPECT_COMMAND_END_ERROR;
			if (lst->separator)
				(*vect)->here->is_delim = 1;
			if (data->is_here_doc)
				is_doc = parse_newline_as_heredoc(vect, data);
		}
		if (lst->content && ft_strstr(lst->content, "<<"))
		{
			to_free = lst;
			data->is_here_doc = 1;
			data->nb_heredoc++;
			is_doc = 1;
		}
		lst = lst->next;
	}
}

char		*form_line_heredoc(t_arg *ar)
{
	t_vect	*vect;
	t_vect	*next_doc;
	t_vect	*vect_to_free;
	t_arg	*arg;
	char	*tmp;
	char	*tmp_nxt;
	char	*new;

	new = NULL;
	tmp = NULL;
	tmp_nxt = NULL;
	next_doc = NULL;
	arg = 
	while (arg && arg->next)
	{
		tmp_nxt = ft_strjoin(arg->content, (arg->next && arg->next->content) ? " " : NULL);
		tmp = ft_strjoin(tmp_nxt, (arg->next) ? arg->next->content : NULL);
		ft_strdel(&tmp_nxt);
		arg = arg->next;
		if (new)
		{
			tmp_nxt = str_join_free(&new, &tmp);
			new = ft_strdup(tmp_nxt);
			ft_strdel(&tmp_nxt);
		}
		else
		{
			new = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
}

int			parse_newline_as_heredoc(t_vect **head, t_bash *data)
{
	t_vect	*vect;
	t_vect	*next_doc;
	t_vect	*vect_to_free;
	t_arg	*arg;
	char	*tmp;
	char	*tmp_nxt;
	char	*new;

	new = NULL;
	tmp = NULL;
	tmp_nxt = NULL;
	next_doc = NULL;
	if (head && *head)
		vect = *head;
	while (vect)
	{
		if (vect->separator == '\n' && (vect_to_free = vect))
		{
			while ((vect = vect->next))
			{
				arg = vect->args;

			}
		}
	}
}
