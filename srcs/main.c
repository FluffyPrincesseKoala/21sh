/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/02 18:59:11 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			main(int argc, char **argv, char **env)
{
	t_bash	data;
	
	(void)argc;
	(void)argv;
	data.env = copy_array(env);
	data.venv = env;
	data.iterator = 0;
	if (!conf_term())
	{
		CLEAR;
		//hello();
		data.column_count = tgetnum("co");
		data.prompt_len = prompt();
		data.vector = vect_new(NULL, NULL);
		loop(data);
	}
	return (0);
}
