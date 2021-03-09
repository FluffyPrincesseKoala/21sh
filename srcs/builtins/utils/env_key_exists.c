/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_key_exists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:54:14 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/09 13:02:38 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int			env_key_exists(char **env, char *key)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strlen(key) == ft_strlendelim(env[i], '=', 0)
			&& ft_strnequ(env[i], key, ft_strlen(key)))
			return (1);
		i++;
	}
	return (0);
}
