/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:51:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/18 19:13:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		print_env(t_bash *data)
{
	print_array(data->env);
}

//setenv lol=caramel
//setenv lol caramel
//setenv PATH $PATH:caramel
//setenv PATH=$PATH:caramel
//setenv ekflbjhriohbjbtio

void		set_env(t_bash *data)
{
	char	*var_to_change;
	char	*key_to_change;
	char	*new;
	char	*tmp;

	var_to_change = NULL;
	key_to_change = NULL;
	new = NULL;
	tmp = NULL;
	while (data->vector && !var_to_change && !key_to_change)
	{
		while (data->vector->args)
		{
			if (ft_strequ(data->vector->args->content, "setenv"))
			{
				//extract var on next args
				data->vector->args = data->vector->args->next;
				if ((var_to_change = ft_strchr(data->vector->args->content, '=')))
				{
					key_to_change = ft_strndup(data->vector->args->content,
						lendelim(data->vector->args->content, '=', 0));
					tmp = ft_strjoin(key_to_change, "=");
					new = ft_strjoin(tmp, (var_to_change + 1));
				}
				else if (data->vector->args->next)
				{
					key_to_change = ft_strdup(data->vector->args->content);
					var_to_change = ft_strdup(data->vector->args->next->content);
					tmp = ft_strjoin(key_to_change, "=");
					new = ft_strjoin(tmp, var_to_change);
				}
				//change env key or create new key
				if (getenv(key_to_change))
					data->env = change_array_value(data->env, key_to_change, new);
				else
					data->env = array_add_value(data->env, new);
				ft_strdel(&new);
				ft_strdel(&tmp);
				ft_strdel(&key_to_change);
			}
			data->vector->args = data->vector->args->next;
		}
		data->vector = data->vector->next;
	}
}
