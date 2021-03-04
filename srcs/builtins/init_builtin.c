/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:13:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 13:31:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		init_builtin(t_built **fct)
{
	if (!(*fct = ft_memalloc(sizeof(t_built) * NB_BUILTIN)))
		return (FAIL);
	(*fct)[0].f = &set_env;
	(*fct)[0].name = ft_strdup("setenv");
	(*fct)[0].len = 6;
	(*fct)[1].f = &unset_env;
	(*fct)[1].name = ft_strdup("unsetenv");
	(*fct)[1].len = 8;
	(*fct)[2].f = &change_directory;
	(*fct)[2].name = ft_strdup("cd");
	(*fct)[2].len = 2;
	(*fct)[3].f = &print_args;
	(*fct)[3].name = ft_strdup("echo");
	(*fct)[3].len = 4;
	(*fct)[4].f = &history;
	(*fct)[4].name = ft_strdup("history");
	(*fct)[4].len = 7;
	(*fct)[5].f = &print_env;
	(*fct)[5].name = ft_strdup("env");
	(*fct)[5].len = 3;
	return (SUCCESS);
}
