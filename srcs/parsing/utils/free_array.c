/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:47:33 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/08 13:32:59 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		ft_strdel(&array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}
