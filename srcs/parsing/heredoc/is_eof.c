/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:50:35 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/10 12:01:14 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/

int	is_eof(t_vect *cmd)
{
	int		current;

	current = 0;
	while (cmd->doc_string && cmd->doc_string[current])
	{
		if (ft_strequ(cmd->eof, cmd->doc_string[current]))
			return (1);
		current++;
	}
	return (0);
}
