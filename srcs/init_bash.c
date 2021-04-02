/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:54:09 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 18:34:57 by cylemair         ###   ########.fr       */
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
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
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
	*fct = ft_memalloc(sizeof(t_built) * NB_BUILTIN);
	if (!(*fct))
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

t_bash	*init_bash(char **env)
{
	t_bash	*data;

	data = ft_memalloc(sizeof(t_bash));
	if (!data)
		return (NULL);
	data->env = copy_env(env);
	if (!data->env)
		return (free_bash(data));
	data->venv = env;
	data->vector = vect_new(NULL, NULL);
	if (!data->vector)
		return (free_bash(data));
	data->redirect_setup = malloc(sizeof(t_redirect_setup) * 4);
	if (!data->redirect_setup)
		return (free_bash(data));
	if (init_redirections_setup_functions(data) == FAIL)
		return (free_bash(data));
	if (init_builtin(&data->builtin) == FAIL)
		return (free_bash(data));
	return (data);
}
