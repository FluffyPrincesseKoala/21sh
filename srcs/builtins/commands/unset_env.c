/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:39:03 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/09 13:08:12 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static char	**del_env_key(char **env, char *key)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((new = malloc(sizeof(char*) * (ft_arraylen(env)))))
	{
		if (env)
		{
			while (env[i])
			{
				if (!ft_strnequ(env[i], key, ft_strlen(key)))
				{
					new[j] = ft_strdup(env[i]);
					j++;
				}
				i++;
			}
			new[j] = NULL;
			free_array(env);
			return (new);
		}
	}
	return (NULL);
}

void		unset_env(t_bash *data, t_vect *command)
{
	t_arg	*argument;
	char	**tmp;
	int		len;

	argument = command->args;
	if (ft_strequ(argument->content, "unsetenv"))
	{
		if ((argument = argument->next))
		{
			if (env_key_exists(data->env, argument->content))
				data->env = del_env_key(data->env, argument->content);
		}
	}
}
