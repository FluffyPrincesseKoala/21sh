/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2021/03/01 19:53:17 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
**	free arg starting from "*head" until's find a t_arg* with "content" inside
**	beware there's sexy redirection inside
*/

static void	free_args_until_eof(t_vect *cmd, t_arg **current)
{
	if (!ft_strequ((*current)->content, cmd->eof))
		free_args_until_eof(cmd, &(*current)->next);
	del_one_arg(*current, cmd);
}

/*
**	create args how are badlly formated (ex: "cat<<lol")
**	by spliting on << character
*/

static int	format_heredoc(t_vect **vect, t_arg **to_check)
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
					add_arg(&new, create_arg(ft_strdup("<<"), NOQUOTE));
				add_arg(&new, create_arg(splited[i], NOQUOTE));
				i++;
			}
			free_all_args(to_check, 0);
			(*vect)->args = new;
			return (1);
		}
	}
	return (0);
}

static int	check_heredoc_format(t_bash *data, t_vect *cmd, t_arg *to_free)
{
	if (!to_free->previous)
		if (!format_heredoc(&cmd, &to_free))
		{
			data->error = SNTX_ERR;
			to_free = reset_data_heredoc(data);
			return ;
		}
		else
			to_free = set_heredoc(data, &cmd, cmd->args);
	if (!data->error && to_free)
		free_args_until_eof(cmd, &to_free);
	else
		return (0);
	return (1);
}

static t_arg	*reset_data_heredoc(t_bash *data)
{
	data->is_here_doc = 0;
	data->nb_heredoc = 0;
	data->finish_heredoc = 0;
	return (NULL);
}

/*
**	parse lst to:
**	get vect->eof
**	count the number of unfinish heredoc and finish one
**	fill vect->doc_string array if there is some "\n" separator
**	return the first arg to free
*/

static t_arg	*set_heredoc(t_bash *data, t_vect **vect, t_arg *lst)
{
	t_arg		*to_free;
	int			is_doc;

	to_free	= NULL;
	is_doc = 0;
	while (lst && lst->content && is_doc != -1)
	{
		if (is_doc == 1)
		{
			if ((*vect)->eof)
				ft_strdel(&(*vect)->eof);
			if (!((*vect)->eof = ft_strdup(lst->content)))
				data->error = UNEXPECT_COMMAND_END_ERROR;
			if (data->is_here_doc)
				is_doc = parse_newline_as_heredoc(vect, data);
		}
		if (lst->content && ft_strstr(lst->content, "<<"))
		{
			if (!to_free)
			{
				to_free = lst;
				data->nb_heredoc++;
			}
			data->is_here_doc = 1;
			is_doc = 1;
		}
		lst = lst->next;
	}
	if (!(*vect)->eof && is_doc)
		data->error = UNEXPECT_COMMAND_END_ERROR;
	return (to_free);
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
				count += check_heredoc_format(data, vect, to_free);
			vect = vect->next;
		}
	}
	if (!data->error)
	{
		data->nb_heredoc = count;
		data->expend = (data->is_here_doc) ? -1 : 0;
	}
}
