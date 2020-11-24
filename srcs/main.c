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
	free_redirections_setup(REDIRECTION_SETUP);
	REDIRECTION_SETUP = NULL;
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
	if (!(REDIRECTION_SETUP = malloc(sizeof(t_redirection_setup) * 4)))
		return (free_bash(data));
	if (!(initialize_redirection_set_up_functions(data)))
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
			CLEAR;
			hello();
			data->prompt_len = prompt(env, 0);
			loop(data);
		}
	}
	else if (argc > 1 && argv)
	{
		if (!(data = initialize_bash(env)))
			puterror(MALLOC_ERROR);
		else
		{
			for (int i = 1 ; i < argc ; i++)
			{
				data->vector->line = ft_strdup(argv[i]);
				if (!is_all_whitespaces(LINE))
				{
					format_line(data);
					search_redirections_in_cmd(data, VECT);
					if (!data->error)
						handle_fork(data, VECT);
				}
				else
					put_error_msg("Shell is not a nudeshell\n");
				if (i + 1 != argc)
					VECT = link_history(&VECT, NULL);
			}
		}
	}
	return (0);
}
