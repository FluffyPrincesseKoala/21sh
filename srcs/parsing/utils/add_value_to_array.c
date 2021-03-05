/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_value_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:07:57 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:27:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**add_value_to_array(char **src, char *value)
{
	char	**new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char*) * (ft_arraylen(src) + 2))))
		return (NULL);
	while (src[i])
	{
		new[i] = ft_strdup(src[i]);
		i++;
	}
	new[i++] = ft_strdup(value);
	new[i] = NULL;
	if (*src)
		free_array(src);
	return (new);
}
