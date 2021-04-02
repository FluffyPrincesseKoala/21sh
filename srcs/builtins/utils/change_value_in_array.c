/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value_in_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:07:05 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:30:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

char	**change_value_in_array(char **src, char *key, char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	while (src && value && src[i])
	{
		if (ft_strnequ(src[i], key, ft_strlen(key)))
		{
			ft_strdel(&src[i]);
			src[i] = ft_strdup(value);
			return (src);
		}
		i++;
	}
	return (src);
}
