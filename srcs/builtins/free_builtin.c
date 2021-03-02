/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:16:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 15:21:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		free_builtin(t_built **fct)
{
	int		i;

	i = 0;
	while (i != NB_BUILTIN && *fct)
	{
		ft_strdel(&(*fct)[i].name);
		(*fct)[i].name = NULL;
		(*fct)[i].f = NULL;
		i++;
	}
	free(*fct);
	*fct = NULL;
	fct = NULL;
}
