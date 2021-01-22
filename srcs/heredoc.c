/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2021/01/22 19:14:18 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		is_env_var(char **env, char *line)
{
	char	*ret;
	char	*tmp;
	char	*potential_shell_var;
	char	*shell_var;
	size_t	len_var;
	size_t	len_space;

	if ((potential_shell_var = ft_strchr(line, '$')))
	{
		len_var = lendelim(potential_shell_var, '$', 0);
		len_space = lendelim(potential_shell_var, ' ', 0);
		shell_var = ft_strndup(potential_shell_var,
			(len_space < len_var) ? len_space : len_var);
		if (!ft_strequ(tmp = use_shell_var(env, shell_var), ""))
		{
			ret = replace_substr(line, shell_var, tmp);
			ft_strdel(&line);
			line = ft_strdup(ret);
			ft_strdel(&ret);
		}
		ft_strdel(&shell_var);
		ft_strdel(&tmp);
	}
}

void	fill_heredoc_array(t_bash *data, t_vect *cmd, char *line)
{
	if (!data->here_doc_delimiter)
		is_env_var(data->env, line);
	if (cmd->doc_string)
		cmd->doc_string = array_add_value(cmd->doc_string, line);
	else
		cmd->doc_string = create_array(line);
}

static void	unlink_free_vector(t_vect **head)
{
	t_vect	*lst;
	t_vect	*nxt_lst;
	t_arg	*nxt_arg;

	if (head && (lst = *head))
	{
		while (lst)
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
		*head = NULL;
		head = NULL;
	}
}

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/

void		is_eof(t_bash *data, t_vect *cmd) // add t_vect
{
	int		current;
	

	current = 0;
	while (cmd->doc_string[current])
	{
		if (ft_strequ(cmd->eof, cmd->doc_string[current]))
		{
			data->here_doc_delimiter = 0;
			data->is_here_doc = data->nb_heredoc - ++data->finish_heredoc;
		}
		current++;
	}
}

void		parse_newline_as_heredoc(t_vect **head, t_bash *data)
{
	t_vect	*vect;
	t_vect	*vect_to_free;

	if (head && *head)
		vect = *head;
	while (vect)
	{
		if (vect->separator == '\n' && (vect_to_free = vect)) // check if there is no more '\n'
		{
			vect->separator = 0;
			while ((vect = vect->next))
				fill_heredoc_array(data, *head, vect->args->content);
			is_eof(data, *head);
			unlink_free_vector(&vect_to_free->next);
		}
		vect = (vect) ? vect->next : NULL;
	}
}

t_arg		*set_heredoc(t_bash *data, t_vect **vect, t_arg *lst)
{
	t_arg	*to_free;
	int		is_doc;

	to_free	= NULL;
	is_doc = 0;
	while (lst && lst->content)
	{
		if (is_doc == 1)
		{
			if (!((*vect)->eof = ft_strdup(lst->content)))
			{
				put_error_msg(SYNTAX);
				put_error_msg("new line\n");
			}
			if (lst->quote)
				data->here_doc_delimiter = 1;
			if (data->is_here_doc)
				parse_newline_as_heredoc(vect, data);
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
	return (to_free);
}

void		here_doc(t_bash *data)
{
	t_arg	*lst;
	t_arg	*to_free;
	t_vect	*vect;
	int		count;

	data->is_here_doc = 0;
	data->nb_heredoc = 0;
	data->finish_heredoc = 0;
	to_free = NULL;
	count = 0;
	if ((vect = data->vector))
	{
		while (vect && (lst = vect->args))
		{
			if ((to_free = set_heredoc(data, &vect, lst)))
			{
				count++;
				to_free->previous->next = NULL;
				free_all_args(&to_free, FALSE);
			}
			vect = vect->next;
		}
	}
	data->nb_heredoc = count;
	data->expend = (data->is_here_doc) ? -1 : 0;
}

int			check_heredoc(t_vect *vector)
{
	t_vect	*vect;
	int		count;

	count = 0;
	if (vector)
	{
		while (vector)
		{
			if (vector->eof)
				count++;
			vector = vector->next;
		}
	}
	return (count);
}

static void	add_at_end_of_last_line(char **dest, char **src)
{
	char	*tmp;

	tmp = ft_strjoin(*dest, "\n");
	ft_strdel(dest);
	*dest = ft_strjoin(tmp, *src);
	ft_strdel(src);
	ft_strdel(&tmp);
}

void		eof_update_heredoc(t_bash *data)
{
	t_vect	*vect;
	int		i;

	i = ++data->finish_heredoc;
	vect = data->vector->up;
	while (vect)
	{
		if (vect->eof)
			i--;
		if (!i)
		{
			add_at_end_of_last_line(&data->vector->up->line, &LINE);
			ft_putchar('\n');
			if (VECT_UP && vect->doc_string && data->nb_heredoc == data->finish_heredoc)
			{
				VECT = VECT_UP;
				free_vector(&data->vector->down, FALSE);
				data->is_here_doc = data->nb_heredoc - data->finish_heredoc;
				data->expend = (data->is_here_doc) ? -1 : 0;
				return ;
			}
		}
		vect = vect->next;
	}
	//error
}

void		update_docstring(t_bash *data)
{
	t_vect	*vect;
	int		i;

	i = data->finish_heredoc;
	vect = data->vector->up;
	while (vect)
	{
		if (!i)
		{
			fill_heredoc_array(data, vect, LINE);
			ft_putchar('\n');
			if (VECT_UP && vect->doc_string)
				add_at_end_of_last_line(&VECT_UP->line, &LINE);
		}
		if (vect->eof)
			i--;
		vect = vect->next;
	}
}

int			is_heredoc_end(t_bash *data, char *line, t_vect *vector)
{
	int		count;

	count = 0;
	while (vector)
	{
		if (count == data->finish_heredoc && ft_strequ(line, vector->eof))
			return (1);
		else if (vector->eof)
			count++;
		vector = vector->next;
	}
	return (0);
}

int			update_heredoc(t_bash *data)
{
	char	**tmp;
	char	*str;

	if (is_heredoc_end(data, LINE, data->vector->up))
		eof_update_heredoc(data);
	else
		update_docstring(data);
	data->y = 0;
	data->x = 0;
}
