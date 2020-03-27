/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 20:04:08 by cylemair         ###   ########.fr       */
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
	if (!conf_term())
	{
		CLEAR;
		//hello();

		loop(data);
	}
	return (0);
}
