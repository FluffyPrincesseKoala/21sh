/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:18:26 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 13:32:11 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** If the arg match a builtin command, add it to the current command structure
*/

void		select_builtin(t_bash *data, t_vect *command)
{
	int	i;

	i = 0;
	while (i != NB_BUILTIN)
	{
		if (ft_strequ(command->args->content, data->builtin[i].name))
			command->builtin = data->builtin[i].f;
		i++;
	}
}
