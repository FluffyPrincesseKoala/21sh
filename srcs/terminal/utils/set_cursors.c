/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:05:26 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:53:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	fill_struct(char *str, char **new_line, int itt[2], int xmax)
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

static void	link_cursor(t_term **head, t_term *new)
{
	t_term	*lst;

	if (head)
	{
		if (!*head && new)
			*head = new;
		else
		{
			lst = *head;
			while (lst->next)
				lst = lst->next;
			lst->next = new;
			new->prev = lst;
		}
	}
}

static t_term	*new_cursor_struct(char *line, int start,
										int max, int prompt)
{
	t_term			*cursor;

	cursor = ft_memalloc(sizeof(t_term));
	if (!cursor)
		return (NULL);
	if (line)
		cursor->line = ft_strdup(line);
	else
		cursor->line = NULL;
	if (start == 0)
		cursor->x_max = max - prompt;
	else
		cursor->x_max = max;
	cursor->line_start = start;
	cursor->line_len = ft_strlen(line);
	cursor->next = NULL;
	cursor->prev = NULL;
	return (cursor);
}

static int	lol(t_term **cursor, char *new_line, int itt[2], int max)
{
	t_term	*new;
	int		start;

	start = itt[0] - itt[1];
	new = new_cursor_struct(new_line, start, max, g_data->prompt_len);
	link_cursor(cursor, new);
	return (FALSE);
}

void	set_cursors(t_bash *data, t_term **cursor, char *str, int max)
{
	int		itt[2];
	int		x_max;
	int		len;
	char	*new_line;

	itt[0] = 0;
	itt[1] = 0;
	len = ft_strlen(str);
	new_line = ft_memalloc(sizeof(char) * (len + 1));
	if (!str || !new_line)
		return ;
	while (str && str[itt[0]])
	{
		if (!*cursor)
			x_max = max - data->prompt_len;
		else
			x_max = max;
		if (fill_struct(str, &new_line, itt, x_max) == 1)
		{
			itt[1] = lolilol(cursor, new_line, itt, max);
			ft_bzero(new_line, len);
		}
	}
	lolilol(cursor, new_line, itt, max);
	ft_strdel(&new_line);
}
