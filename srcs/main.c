/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/22 19:49:09 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_bash	*initialize_bash(char **env)
{
	t_bash	*data;

	if (!(data = malloc(sizeof(t_bash))))
		return (NULL);
	if (!(data->env = copy_array(env)))
		return (NULL);
	data->venv = env;
	data->iterator = 0;
	data->count_separator = 0;
	data->error = NULL;
	if (!(data->vector = vect_new(NULL, NULL)))
		return (NULL);
	data->prompt_len = prompt();

	return (data);
}

int		main(int argc, char **argv, char **env)
{
	t_bash	*data;
	
	(void)argc;
	(void)argv;
	if (!conf_term())
	{
		CLEAR;
		if (!(data = initialize_bash(env)))
			puterror("c'est pas bien");
		else
			loop(data);
	}
	return (0);
}
