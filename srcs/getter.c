/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 18:42:41 by cylemair          #+#    #+#             */
/*   Updated: 2020/05/22 19:28:50 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		pull_line(t_vect **head)
{
	t_vect	*lst;
	
	if (head && *head)
	{
		lst = *head;
		while (lst->down)
			lst = lst->down;
		ft_strdel(&lst->line);
		lst->line = ft_strdup((*head)->line);
		*head = lst;
	}
}

void		push_entry(t_bash *data, char *entry, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (data->iterator || *line)
		tmp = addchar(*line, entry[0], data->iterator);
	else
		tmp = ft_strndup(entry, 1);
	if (ft_strlen(*line))
		ft_strdel(&*line);
	*line = ft_strdup(tmp);
	ft_strdel(&tmp);
}

int		handle_new_entry(t_bash *data, char *entry, int pos)
{
	if (!data->vector->line)
		data->vector->line = ft_strndup(entry, 1);
	else
	{
		if (data->vector->down)
			pull_line(&data->vector);
		push_entry(data, entry, &data->vector->line);
	}
	SAVE_C;
	data->iterator = pos;
	print_rest(data->vector->line, pos, NULL);
	RESET_C;
	arrow_right(data);
	return (data->iterator);
}

int					print_expend(char *str, int pos, char *old)
{
	while (str && str[pos])
	{
		ft_putchar(str[pos]);
		if (str[pos] == '\n')
			ft_putchar('>');
		pos++;
	}
	if (old && pos < ft_strlen(old))
	{
		while (old[pos])
		{
			ft_putchar(' ');
			pos++;
		}
	}
	return (pos);
}

int		handle_expend(t_bash *data, char *entry, int pos)
{
	if (!data->vector->line)
		data->vector->line = ft_strndup(entry, 1);
	else
	{
		if (data->vector->down)
			pull_line(&data->vector);
		push_entry(data, entry, &data->vector->line);
	}
	SAVE_C;
	data->iterator = pos;
	print_expend(data->vector->line, pos, NULL);
	RESET_C;
	arrow_right(data);
	return (data->iterator);
}