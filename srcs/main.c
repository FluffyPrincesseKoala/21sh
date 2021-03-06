/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:01:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:06:19 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int		main(int argc, char **argv, char **env)
{
	t_bash	*data;

	if (argc == 1)
	{
		if (!(data = init_bash(env)))
			put_error_msg("Malloc failed.\n");
		else if (!conf_term())
		{
			g_data = data;
			clear();
			data->prompt_len = prompt(env, 0);
			loop(data);
			print_history(data);
			unconf_term();
			free_bash(data);
		}
	}
	return (0);
}
