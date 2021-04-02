/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:39:03 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:23:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static char	**del_env_key(char **env, char *key)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = malloc(sizeof(char *) * (ft_arraylen(env)));
	if (new)
	{
		if (env)
		{
			while (env[++i])
			{
				if (!ft_strnequ(env[i], key, ft_strlen(key)))
				{
					new[j] = ft_strdup(env[i]);
					j++;
				}
			}
			new[j] = NULL;
			free_array(env);
			return (new);
		}
	}
	return (NULL);
}

void	unset_env(t_bash *data, t_vect *command)
{
	t_arg	*argument;
	char	**tmp;
	int		len;

	argument = command->args;
	if (ft_strequ(argument->content, "unsetenv"))
	{
		argument = argument->next;
		if (argument)
		{
			if (env_key_exists(data->env, argument->content))
				data->env = del_env_key(data->env, argument->content);
		}
	}
}
