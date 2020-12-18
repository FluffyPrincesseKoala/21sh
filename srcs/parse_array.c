/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/25 10:49:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**array_add_value(char **src, char *value)
{
	char	**new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char*) * (array_len(src) + 2))))
		return (NULL);
	while (src[i])
	{	
		new[i] = ft_strdup(src[i]);
		i++;
	}
	new[i++] = ft_strdup(value);
	new[i] = NULL;
	free_array(src);
	return (new);
}

char		**change_array_value(char **src, char *key, char *value)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (ft_strnequ(src[i], key, ft_strlen(key)))
			src[i] = ft_strdup(value);
		i++;
	}
	return (src);
}

int			is_env_key_exist(char **env, char *key)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], key, ft_strlen(key)))
			return (1);
		i++;
	}
	return (0);
}
