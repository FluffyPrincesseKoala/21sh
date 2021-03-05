/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:22:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 14:29:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
**	explicitly return the current vector ( one that's not finish )
*/

static t_vect	*get_current_heredoc_vector(t_bash *data)
{
	t_vect	*current;

	current = data->vector->up;
	while (current)
	{
		if (current->eof && !is_eof(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*
**	on sub-prompt all line are added to the previous with a "\n" between
*/

static void		add_at_end_of_last_line(char **dest, char **src)
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

static void		eof_update_heredoc(t_bash *data)
{
	t_vect	*cmd;
	int		i;

	++data->finish_heredoc;
	cmd = get_current_heredoc_vector(data);
	if (cmd)
		fill_heredoc_array(data, cmd, &LINE);
	add_at_end_of_last_line(&data->vector->up->line, &LINE);
	ft_putchar('\n');
	if (VECT_UP && data->nb_heredoc == data->finish_heredoc)
	{
		VECT = VECT_UP;
		free_vector(&data->vector->down, FALSE);
		data->is_heredoc = data->nb_heredoc - data->finish_heredoc;
		data->expend = (data->is_heredoc) ? -1 : 0;
		return ;
	}
}

/*
**	add line to current doc_array and to last line (vector->up)
*/

static void		update_docstring(t_bash *data)
{
	t_vect	*cmd;
	int		i;

	i = data->finish_heredoc;
	if (cmd = get_current_heredoc_vector(data))
	{
		fill_heredoc_array(data, cmd, &LINE);
		ft_putchar('\n');
		if (VECT_UP && cmd->doc_string)
			add_at_end_of_last_line(&VECT_UP->line, &LINE);
	}
}

/*
**	update heredoc_array
*/

int				update_heredoc(t_bash *data)
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
