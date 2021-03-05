/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:05:26 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 17:25:26 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int		fill_struct(char *str, char **new_line, int itt[2], int xmax)
{
	if (itt[1] != xmax && str[itt[0]] != '\n')
	{
		(*new_line)[itt[1]] = str[itt[0]];
		itt[1]++;
		itt[0]++;
		return (0);
	}
	else
	{
		if (str[itt[0]] == '\n')
		{
			(*new_line)[itt[1]] = str[itt[0]];
			itt[1]++;
			itt[0]++;
		}
		(*new_line)[itt[1]] = '\0';
		return (1);
	}
}

static void		link_cursor(t_term **head, t_term *new)
{
	t_term	*lst;

	if (!*head && new)
	{
		*head = new;
	}
	else
	{
		lst = *head;
		while (lst->next)
			lst = lst->next;
		lst->next = new;
		new->prev = lst;
	}
}

static t_term	*new_cursor_struct(char *line, int start,
										int max, int prompt)
{
	t_term			*cursor;

	if (!(cursor = ft_memalloc(sizeof(t_term))))
		return (NULL);
	cursor->line = (line) ? ft_strdup(line) : NULL;
	cursor->x_max = (start == 0) ? max - prompt : max;
	cursor->line_start = start;
	cursor->line_len = ft_strlen(line);
	cursor->next = NULL;
	cursor->prev = NULL;
}

void			set_cursors(t_bash *data, t_term **cursor, char *str, int max)
{
	int		itt[2];
	int		x_max;
	int		len;
	char	*new_line;

	itt[0] = 0;
	itt[1] = 0;
	len = ft_strlen(str);
	if (!str
		|| !(new_line = ft_memalloc(sizeof(char) * (len + 1))))
		return ;
	while (str && str[itt[0]])
	{
		x_max = (!*cursor) ? max - data->prompt_len : max;
		if (fill_struct(str, &new_line, itt, x_max) == 1)
		{
			link_cursor(cursor, new_cursor_struct(new_line,
				itt[0] - itt[1], max, data->prompt_len));
			itt[1] = 0;
			ft_bzero(new_line, len);
		}
	}
	link_cursor(cursor, new_cursor_struct(new_line,
		itt[0] - itt[1], max, data->prompt_len));
	ft_strdel(&new_line);
}
