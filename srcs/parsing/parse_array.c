/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 12:54:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**create_array(char *first)
{
	char	**ret;

	if (!(ret = malloc(sizeof(char *) * (2))))
		return (NULL);
	ret[0] = ft_strdup(first);
	ret[1] = NULL;
	return (ret);
}

char		**array_add_value(char **src, char *value)
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

char		**change_array_value(char **src, char *key, char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	while (src[i])
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
