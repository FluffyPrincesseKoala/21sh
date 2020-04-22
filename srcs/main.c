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

int			main(int argc, char **argv, char **env)
{
	t_bash	*data;
	
	(void)argc;
	(void)argv;
	if (!(data = malloc(sizeof(t_bash))))
		return (1);
	if (!conf_term())
	{
		CLEAR;
		//hello();
		data->env = copy_array(env);
		data->venv = env;
		data->iterator = 0;
		data->count_separator = 0;
		data->error = NULL;
		data->vector = vect_new(NULL, NULL);
		data->prompt_len = prompt();
//		debug_loop_try_termcaps(data);
		loop(data);
	}
	return (0);
}
