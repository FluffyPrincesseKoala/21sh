/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_from_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:48:39 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

char		*get_value_from_env(char **env, char *var)
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
