/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:58:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 19:53:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_array(char **array)
{
	char	**new;
	int		i;

	i = 0;
	while (array[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char		*findenv(char **env, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = lendelim(var, '=', 0);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			return (*(env + i) + len + 1);
		i += 1;
	}
	return (NULL);
}

char		**delenv(char **env, char *var)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!(new = malloc(sizeof(char*) * (array_len(env)))))
		return (NULL);
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)))
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
	}
	if (i == j)
	{
		while (j--)
			ft_strdel(&new[j]);
		free(new);
		return (env);
	}
	new[j] = NULL;
	return (new);
}

char		**addenv(char **env, char *var)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	i++;
	new[i] = NULL;
	return (new);
}
