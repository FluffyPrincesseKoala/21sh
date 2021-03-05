/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:56:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 11:56:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
**	check if all the heredoc are completed
*/

int	is_heredoc_end(t_bash *data, char *line, t_vect *vector)
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
