/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2021/03/04 17:43:29 by koala            ###   ########.fr       */
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
					add_arg(&new, create_arg(ft_strdup("<<")));
				add_arg(&new, create_arg(splited[i]));
				i++;
			}
			free_all_args(to_check, 0);
			(*vect)->args = new;
			return (1);
		}
	}
	return (0);
}

static t_arg	*reset_data_heredoc(t_bash *data)
{
	data->is_heredoc = 0;
	data->nb_heredoc = 0;
	data->finish_heredoc = 0;
	return (NULL);
}

static int	check_heredoc_format(t_bash *data, t_vect *cmd, t_arg *to_free)
{
	if (to_free && !to_free->previous)
	{
		if (!format_heredoc(&cmd, &to_free))
		{
			data->error = SNTX_ERR;
			to_free = reset_data_heredoc(data);
			return (-1);
		}
		else
			to_free = set_heredoc(data, &cmd);
	}
	if (to_free && !data->error)
		free_args_until_eof(cmd, &to_free);
	else
		return (0);
	return (1);
}

/*
**	shearch heredoc parametere and free there args (for parameter)
**	and vector (for heredoc string)
*/

void		heredoc(t_bash *data)
{
	t_vect	*cmd;
	int		count;

	reset_data_heredoc(data);
	count = 0;
	if ((cmd = data->vector))
	{
		while (cmd && cmd->args && !data->error)
		{
			count += check_heredoc_format(data, cmd, set_heredoc(data, &cmd));
			cmd = cmd->next;
		}
	}
	if (!data->error)
	{
		data->nb_heredoc = count;
		data->expend = (data->is_heredoc) ? -1 : 0;
	}
}
