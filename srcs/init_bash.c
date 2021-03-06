/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:54:09 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:58:41 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static char	**copy_env(char **array)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	while (array[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

static int	init_builtin(t_built **fct)
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

t_bash		*init_bash(char **env)
{
	t_bash	*data;

	if (!(data = ft_memalloc(sizeof(t_bash))))
		return (NULL);
	if (!(data->env = copy_env(env)))
		return (free_bash(data));
	data->venv = env;
	if (!(data->vector = vect_new(NULL, NULL)))
		return (free_bash(data));
	if (!(data->redirect_setup = malloc(sizeof(t_redirect_setup) * 4)))
		return (free_bash(data));
	if (init_redirections_setup_functions(data) == FAIL)
		return (free_bash(data));
	if (init_builtin(&data->builtin) == FAIL)
		return (free_bash(data));
	return (data);
}
