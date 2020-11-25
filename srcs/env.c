/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:51:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/25 15:20:30 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		print_env(t_bash *data)
{
	//print_array(data->env);
	for (int i = 0 ; data->env[i] ; i++) {
		ft_putnbr(i);
		ft_putchar('|');
		ft_putendl(data->env[i]);
	}
}

// SETENV TEST EXEMPLE
//setenv lol=caramel
//setenv lol caramel
//setenv PATH $PATH:caramel
//setenv PATH=$PATH:caramel
//setenv ekflbjhriohbjbtio
//setenv NULL

static char	*create_new_env_key(t_arg *args, char **key)
{
	char	*var;
	char	*new;
	char	*tmp;

	new = NULL;
	if ((var = ft_strdup(ft_strchr(args->content, '='))))
	{
		*key = ft_strndup(args->content, lendelim(args->content, '=', 0));
		tmp = ft_strjoin(*key, "=");
		new = ft_strjoin(tmp, (var + 1));
		ft_strdel(&tmp);
		ft_strdel(&var);
	}
	else if (args->next)
	{
		*key = ft_strdup(args->content);
		var = ft_strdup(args->next->content);
		tmp = ft_strjoin(*key, "=");
		new = ft_strjoin(tmp, var);
		ft_strdel(&tmp);
		ft_strdel(&var);
	}
	return (new);
}

void		set_env(t_bash *data)
{
	char	*key_to_change;
	char	*new;

	new = NULL;
	key_to_change = NULL;
	if (VECT)
	{
		while (VECT->args)
		{
			if (ft_strequ(VECT->args->content, "setenv"))
			{
				VECT->args = VECT->args->next;
				if (VECT->args)
					new = create_new_env_key(VECT->args, &key_to_change);
				if (is_env_key_exist(data->env, key_to_change))
					data->env = change_array_value(data->env, key_to_change, new);
				else
					data->env = array_add_value(data->env, new);
				ft_strdel(&new);
				ft_strdel(&key_to_change);
				return ;
			}
			VECT->args = VECT->args->next;
		}
	}
}

static char	**del_env_key(char **env, char *key)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char*) * (array_len(env)))))
		return (NULL);
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

void		unset_env(t_bash *data)
{
	char	*key;

	key = NULL;
	while (VECT->args)
	{
		if (ft_strequ(VECT->args->content, "unsetenv"))
		{
			if ((VECT->args = VECT->args->next))
			{
				if ((key = ft_strndup(VECT->args->content,
						lendelim(VECT->args->content, '=', 0))))
					data->env = del_env_key(data->env, key);
				return ;
			}
		}
		VECT->args = VECT->args->next;
	}
}
