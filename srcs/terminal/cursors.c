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

void			clear_struct(t_term **cursor)
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

/*
**	goto cursor_struct that contain current line
**	goto current iterator
**	fill & return struct
*/

t_term	*find_cursor_node(t_term **head, int total_len, int idx_max, int plen)
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
			while (curr->line && curr->line[i] && count != total_len)
			{
				count++;
				i++;
			}
			if ((i < curr->line_len && count == total_len) || !curr->next)
				return (curr);
			curr = curr->next;
			if (count == total_len)
				return (curr);
		}
	}
	return (NULL);
}

int		get_win_max_col(void)
{
	struct winsize	w;

	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
		return (w.ws_col);
	return (0);
}
