/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:22:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:59:17 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

static void	eof_update_heredoc(t_bash *data)
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
			if (data->vector->up)
				fill_heredoc_array(data, data->vector->up, &LINE);
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
		vect = vect->next;
	}
}

/*
**	add line to current doc_array and to last line (vector->up)
*/

static void	update_docstring(t_bash *data)
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
			fill_heredoc_array(data, cmd, &LINE);
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

static int	is_heredoc_end(t_bash *data, char *line, t_vect *vector)
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
