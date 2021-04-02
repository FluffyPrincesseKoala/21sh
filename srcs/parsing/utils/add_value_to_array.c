/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_value_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:07:57 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:24:46 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	add_value_to_array(char ***src, char *value)
{
	char	**new;
	int		len;
	int		i;

	i = -1;
	len = ft_arraylen((*src));
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
	{
		g_data->error = MALLOC_ERROR;
		return ;
	}
	while ((*src) && (*src)[++i])
		new[i] = ft_strdup((*src)[i]);
	new[i] = ft_strdup(value);
	new[i + 1] = NULL;
	if ((*src) && *(*src))
	{
		free_array((*src));
		(*src) = new;
	}
}
