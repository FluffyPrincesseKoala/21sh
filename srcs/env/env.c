/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:51:15 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/19 19:59:35 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void			print_env(t_bash *data, t_vect *cmd)
{
	
	for (int i = 0 ; data->env[i] ; i++) {
		ft_putnbr(i);
		ft_putchar('|');
		ft_putendl(data->env[i]);
	}
}

static char	*create_new_env_key(t_arg *args, char **key)
{
	char	*var;
	char	*new;
	char	*tmp;

	new = NULL;
	if ((var = ft_strdup(ft_strchr(args->content, '='))))
	{
		*key = ft_strndup(args->content, ft_strlendelim(args->content, '=', 0));
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

void		set_env(t_bash *data, t_vect *command)
{
	char	*key_to_change;
	char	*new;
	t_arg	*arg;

	new = NULL;
	key_to_change = NULL;
	if (command)
	{
		arg = command->args;
		while (arg)
		{
			if (ft_strequ(arg->content, "setenv"))
			{
				arg = arg->next;
				if (arg)
					new = create_new_env_key(arg, &key_to_change);
				if (is_env_key_exist(data->env, key_to_change))
					data->env = change_array_value(data->env, key_to_change, new);
				else
					data->env = array_add_value(data->env, new);
				ft_strdel(&new);
				ft_strdel(&key_to_change);
				return ;
			}
			arg = arg->next;
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
	char	*key;
	char	**tmp;
	int		len;

	key = NULL;
	argument = command->args;
	if (ft_strequ(argument->content, "unsetenv"))
	{
		if ((argument = argument->next))
		{
			len = ft_strlendelim(argument->content, '=', 0);
			key = ft_strndup(argument->content, len);
			if (is_env_key_exist(data->env, key))
				data->env = del_env_key(data->env, key);
			ft_strdel(&key);
		}
	}
}
