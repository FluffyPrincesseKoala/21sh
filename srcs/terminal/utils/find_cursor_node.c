/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cursor_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:20:20 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/15 20:31:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

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
