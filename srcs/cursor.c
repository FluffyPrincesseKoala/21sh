/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:05:26 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/02 13:00:42 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int					count_delim_befor(char *str, int pos, char delim)
{
	int				i;
	int				count;

	i = (str[pos] == delim) ? 1 : 0;
	count = 0;
	while (str && pos && str[pos - i])
	{
		if (str[i - pos] == delim)
			count++;
		i++;
	}
	return (count);
}

int					get_y_cursor(t_term *src)
{
	int				count;

	count = 0;
	while (src->prev)
	{
		src = src->prev;
		count += 1;
	}
	return (count);
}

void				clear_struct(t_term **cursor)
{
	t_term			*cur;
	t_term			*nxt;

	if (*cursor)
	{
		cur = *cursor;
		while (cur->prev)
			cur = cur->prev;
		while (cur)
		{
			ft_strdel(&cur->line);
			nxt = cur->next;
			free(cur);
			cur = nxt;
		}
		cur = NULL;
		*cursor = NULL;
		cursor = NULL;
	}
}

t_term				*new_cursor_struct(char *line, int end, int start)
{
	t_term			*cursor;

	if (!(cursor = ft_memalloc(sizeof(t_term))))
		return (NULL);
	cursor->line = (line) ? ft_strdup(line) : NULL;
	cursor->line_end = end;
	cursor->line_start = start;
	cursor->iterator = 0;
	cursor->x = 0;
	cursor->y = 0;
	cursor->next = NULL;
	cursor->prev = NULL;
}

void	link_cursor(t_term **head, t_term *new)
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

static void cursor_print(t_term *curr)
{
	printf("x:%d y:%d ls:%d le:%d idx:%d c:[%c] len:%d\n[%s]\n",curr->x, curr->y,
	curr->line_start, curr->line_end, curr->iterator,
	curr->line[curr->x], ft_strlen(curr->line), curr->line);
}

void	currsor_info(t_term *curr)
{
	SAVE_C;
	GOTO(0, 0);
	hello();
	GOTO(0, 0);
	cursor_print(curr);
	RESET_C;
}

t_term 	*init_xy_curr(t_term *curr, int count, int i, int max)
{
	curr->iterator = count;
	if (curr->line[i] || count == max)
	{
		curr->x = i;
		curr->y = get_y_cursor(curr);
	}
	else
	{
		curr->x = 0;
		curr->y = get_y_cursor(curr) + 1;
	}
	currsor_info(curr);
	return (curr);
}
/*
**	goto cursor_struct that contain current line
**	goto current iterator
**	fill & return struct
*/
t_term	*find_node_by_iterator(t_term **head, int idx, int idx_max)
{
	t_term	*curr;
	int		i;
	int		count;

	count = 0;
	if (*head)
	{
		curr = *head;
		while (curr)
		{
			i = 0;
			while (curr->line && curr->line[i] && count != idx)
			{
				count++;
				i++;
			}
			if (count == idx)
				return (init_xy_curr(curr, count, i, idx_max));
			curr = curr->next;
		}
		*head = curr;
	}
	return ((*head) ? init_xy_curr(*head, count, i, idx_max) : NULL);
}

int		get_win_max_col(void)
{
	struct winsize	w;

	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
		return (w.ws_col);
	return (0);
}

void	fit_line_in_terminal(t_bash *data, t_term **cursor, char *str, int max)
{
	int		i;
	int		j;
	int		x_max;
	int		len;
	char	*new_line;

	i = 0;
	j = 0;
	if (!str
	|| !(new_line = ft_memalloc(sizeof(char) * ((len = ft_strlen(str)) + 1))))
		return ;
	while (str && str[i])
	{
		x_max = (!*cursor) ? max - data->prompt_len : max ;
		if (j != x_max && str[i] != '\n')
		{
			new_line[j] = str[i];
			j++;
			i++;
		}
		if (j == x_max || str[i] == '\n')
		{
			if ( str[i] == '\n')
			{
				new_line[j] = str[i];
				j++;
				i++;
			}
			new_line[j] = '\0';
			link_cursor(cursor, new_cursor_struct(new_line, j, i - j));
			ft_bzero(new_line, len);
			j = 0;
		}
	}
	link_cursor(cursor, new_cursor_struct(new_line, x_max, i - j));
	ft_bzero(new_line, len);
}

void				init_cursor(t_bash *data)
{
	data->cursor = ft_memalloc(sizeof(t_term));
}
