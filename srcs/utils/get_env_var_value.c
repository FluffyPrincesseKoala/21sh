/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:17:32 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:29:26 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

char	*get_value_from_env(char **env, char *var)
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
