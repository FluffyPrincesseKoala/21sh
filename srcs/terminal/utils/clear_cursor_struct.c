/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cursor_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:19:19 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	clear_cursor_struct(t_term **cursor)
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
