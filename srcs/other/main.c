/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/25 14:43:45 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

void	free_redirectionss_setup(t_redirection_setup **redirections_setup)
{
	int		i;

	if (redirections_setup)
	{
		i = 0;
		while (redirections_setup[i])
		{
			ft_strdel(&redirections_setup[i]->op);
			free(redirections_setup[i]);
			i++;
		}
		free(redirections_setup);
	}
}

static void	free_all_vectors(t_vect *vect)
{
	if (vect)
	{
		ft_strdel(&vect->line);
		ft_strdel(&vect->eof);
		free_array(vect->doc_string);
		free_all_args(&vect->args, FALSE);
		free_all_vectors(vect->next);
		free_all_vectors(vect->up);
		if (vect->redirections)
			free_redirections(vect);
		vect->args = NULL;
		vect->next = NULL;
		vect->up = NULL;
		vect->down = NULL;
		vect->redirections = NULL;
		vect->line = NULL;
		free(vect);
		vect = NULL;
	}
}

void		*free_bash(t_bash *data)
{
	if (data->env)
		free_array(data->env);
	if (data->args_array)
		free_array(data->args_array);
	data->env = NULL;
	data->venv = NULL;
	free_all_vectors(data->vector);
	free_redirectionss_setup(REDIRECTIONS_SETUP);
	REDIRECTIONS_SETUP = NULL;
	free_builtin(&data->builtin);
	ft_strdel(&data->eof);
	ft_strdel(&data->copied);
	ft_strdel(&data->path);
	free(data);
	data = NULL;
	arrow_key(NULL, NULL);
	return (NULL);
}

t_bash	*initialize_bash(char **env)
{
	t_bash	*data;

	if (!(data = ft_memalloc(sizeof(t_bash))))
		return (NULL);
	if (!(data->env = copy_env(env)))
		return (free_bash(data));
	data->venv = env;
	if (!(data->vector = vect_new(NULL, NULL)))
		return (free_bash(data));
	if (!(REDIRECTIONS_SETUP = malloc(sizeof(t_redirection_setup) * 4)))
		return (free_bash(data));
	if (init_redirections_setup_functions(data) == FAIL)
		return (free_bash(data));
	if (init_builtin(&data->builtin) == FAIL)
		return (free_bash(data));
	return (data);
}

int		main(int argc, char **argv, char **env)
{
	t_bash	*data;
	
	if (argc == 1)
	{
		if (!(data = initialize_bash(env)))
			puterror(MALLOC_ERROR);
		else if (!conf_term())
		{
			data_g = data;
			CLEAR;
			data->prompt_len = prompt(env, 0);
			loop(data);
			print_history(data);
			unconf_term();
			free_bash(data);
		}
	}
	return (0);
}
