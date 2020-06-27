/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/12 17:28:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	free_redirections_setup(t_redirection_setup **redirections_setup)
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

void	*free_bash(t_bash *data)
{
	free_array(data->env);
	free_array(data->venv);
	data->env = NULL;
	data->venv = NULL;
	free_all_vectors(data->vector);
	free_redirections_setup(data->redirections_setup);
	data->redirections_setup = NULL;
	free(data);
	return (NULL);
}

t_bash	*initialize_bash(char **env)
{
	t_bash	*data;

	if (!(data = ft_memalloc(sizeof(t_bash))))
		return (NULL);
	if (!(data->env = copy_array(env)))
		return (free_bash(data));
	data->venv = env;
	if (!(data->vector = vect_new(NULL, NULL)))
		return (free_bash(data));
	data->prompt_len = prompt(0);
	if (!(data->redirections_setup = malloc(sizeof(t_redirection_setup) * 4)))
		return (free_bash(data));
	if (!(initialize_redirection_set_up_functions(data)))
		return (free_bash(data));
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
		hello();
		if (!(data = initialize_bash(env)))
			puterror("c'est pas bien");
		else
			loop(data);
	}
	return (0);
}
