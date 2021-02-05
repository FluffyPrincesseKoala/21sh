/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:23:17 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/05 12:46:27 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains function concerning builtin commands parsing and related
**  builtin functions.
*/

int		init_built_in(t_built **fct)
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

void		free_builtin(t_built **fct)
{
	int		i;

	i = 0;
	while (i != NB_BUILTIN && *fct)
	{
		ft_strdel(&(*fct)[i].name);
		(*fct)[i].name = NULL;
		(*fct)[i].f = NULL;
		i++;
	}
	free(*fct);
	*fct = NULL;
	fct = NULL;
}

int			is_exit(t_vect *command)
{
	if (ft_strequ(command->args->content, "exit"))
		return (TRUE);
	return (FALSE);
}

/*
** If the arg match a builtin command, add it to the current command structure
*/

void		search_built_in(t_bash *data, t_vect *command)
{
	int	i;

	i = 0;
	while (i != NB_BUILTIN)
	{
		if (ft_strequ(command->args->content, data->builtin[i].name))
			command->builtin = data->builtin[i].f;
		i++;
	}
}