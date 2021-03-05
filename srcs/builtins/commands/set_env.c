/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:39:59 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 11:33:24 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
	arg = command->args;
	while (arg)
	{
		if (ft_strequ(arg->content, "setenv"))
		{
			arg = arg->next;
			if (arg)
				new = create_new_env_key(arg, &key_to_change);
			if (env_key_exists(data->env, key_to_change))
				data->env = change_value_in_array(data->env,
					key_to_change, new);
			else
				data->env = add_value_to_array(data->env, new);
			ft_strdel(&new);
			ft_strdel(&key_to_change);
			return ;
		}
		arg = arg->next;
	}
}
