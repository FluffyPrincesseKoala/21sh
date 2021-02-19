/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2021/02/19 18:53:56 by koala            ###   ########.fr       */
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
		len_var = ft_strlendelim(potential_shell_var, '$', 0);
		len_space = ft_strlendelim(potential_shell_var, ' ', 0);
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

t_arg	*reset_data_heredoc(t_bash *data)
{
	data->is_here_doc = 0;
	data->nb_heredoc = 0;
	data->finish_heredoc = 0;
	return (NULL);
}

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/

int		is_eof(t_bash *data, t_vect *cmd) // add t_vect
{
	int		current;
	

	current = 0;
	while (cmd->doc_string[current])
	{
		if (ft_strequ(cmd->eof, cmd->doc_string[current]))
		{
			data->here_doc_delimiter = 0;
			data->is_here_doc = data->nb_heredoc - ++data->finish_heredoc;
			return (1);
		}
		current++;
	}
	return (0);
}

int		parse_newline_as_heredoc(t_vect **head, t_bash *data)
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
			next_doc = (*head);
			while ((vect = vect->next))
			{
				arg = vect->args;
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
				fill_heredoc_array(data, next_doc, (new) ? new : arg->content);
				ft_strdel(&new);
				if (is_eof(data, next_doc))
				{
					next_doc = vect->next;
					unlink_free_vector(&vect_to_free, (next_doc) ? next_doc : NULL);
					return (-1);
				}
			}
			unlink_free_vector(&vect_to_free, NULL);
		}
		vect = (vect) ? vect->next : NULL;
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

t_arg		*set_heredoc(t_bash *data, t_vect **vect, t_arg *lst)
{
	t_arg	*to_free;
	int		is_doc;

	to_free	= NULL;
	is_doc = 0;
	while (lst && lst->content && is_doc != -1)
	{
		if (is_doc == 1)
		{
			if (!((*vect)->eof = ft_strdup(lst->content)))
				data->error = UNEXPECT_COMMAND_END_ERROR;
			if (lst->quote)
				data->here_doc_delimiter = 1;
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
	if (!(*vect)->eof && is_doc)
		data->error = UNEXPECT_COMMAND_END_ERROR;
	return (to_free);
}

/*
**	free arg starting from "*head" until's find a t_arg* with "content" inside
**	beware there's sexy redirection inside
*/


void	free_args_until_eof(t_vect *cmd, t_arg **current)
{
	if (!ft_strequ((*current)->content, cmd->eof))
		free_args_until_eof(cmd, &(*current)->next);
	del_one_arg(*current, cmd);
}

/*
**	create args how are badlly formated (ex: "cat<<lol")
**	by spliting on << character
*/

int			format_heredoc(t_vect **vect, t_arg **to_check)
{
	t_arg	*new;
	char	**splited;
	int		len;
	int		i;

	i = 0;
	new = NULL;
	if ((splited = ft_strsplit((*to_check)->content, '<')))
	{
		if ((len = ft_arraylen(splited)) >= 2)
		{
			while (splited[i])
			{
				if (i == 1)
					add_arg(&new, new_arg(ft_strdup("<<"), NOQUOTE));
				add_arg(&new, new_arg(splited[i], NOQUOTE));
				i++;
			}
			free_all_args(to_check, 0);
			(*vect)->args = new;
			return (1);
		}
	}
	return (0);
}



/*
**	shearch heredoc parametere and free there args (for parameter)
**	and vector (for heredoc string)
*/

void		here_doc(t_bash *data)
{
	t_arg	*lst;
	t_arg	*to_free;
	t_vect	*vect;
	int		count;

	to_free = reset_data_heredoc(data);
	count = 0;
	if ((vect = data->vector))
	{
		while (vect && (lst = vect->args) && !data->error)
		{
			if ((to_free = set_heredoc(data, &vect, lst)))
			{
				count++;
				if (!to_free->previous)
					if (!format_heredoc(&vect, &to_free))
					{
						data->error = SNTX_ERR;
						to_free = reset_data_heredoc(data);
						return ;
					}
					else
						to_free = set_heredoc(data, &vect,vect->args);
				if (!data->error && to_free)
					free_args_until_eof(vect, &to_free);
				}
			vect = vect->next;
		}
	}
	if (!data->error)
	{
		data->nb_heredoc = count;
		data->expend = (data->is_here_doc) ? -1 : 0;
	}
}

/*
**	on sub-prompt all line are added to the previous with a "\n" between
*/

static void	add_at_end_of_last_line(char **dest, char **src)
{
	char	*tmp;

	tmp = ft_strjoin(*dest, "\n");
	ft_strdel(dest);
	*dest = ft_strjoin(tmp, *src);
	ft_strdel(src);
	ft_strdel(&tmp);
}

/*
**	update the current vector->doc_string
*/

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
			if (VECT_UP && data->nb_heredoc == data->finish_heredoc)
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

/*
**	add line to current doc_array and to last line (vector->up)
*/

void		update_docstring(t_bash *data)
{
	t_vect	*cmd;
	int		i;

	i = data->finish_heredoc;
	cmd = data->vector->up;
	while (cmd && !cmd->eof)
		cmd = cmd->next;
	while (cmd)
	{
		while (cmd && !cmd->eof)
			cmd = cmd->next;
		if (!i)
		{
			fill_heredoc_array(data, cmd, LINE);
			ft_putchar('\n');
			if (VECT_UP && cmd->doc_string)
				add_at_end_of_last_line(&VECT_UP->line, &LINE);
		}
		if (cmd && cmd->eof)
			i--;
		cmd = (cmd) ? cmd->next : NULL;
	}
}

/*
**	check if all the heredoc are completed
*/

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

/*
**	update heredoc_array
*/

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
