/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:48:39 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 12:49:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*get_env_var_value(char **env, char *var)
{
	int		i;
	int		len;

	i = 0;
	while (env && env[i])
	{
		len = ft_strlendelim(env[i], '=', 0);
		if (ft_strlen(var) == len && !ft_strncmp(env[i], var, len))
			return (*(env + i) + len + 1);
		i += 1;
	}
	return (NULL);
}
