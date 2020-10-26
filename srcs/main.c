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

t_bash	*initialize_bash(char **env, int type)
{
	t_bash	*data;

	if (!(data = ft_memalloc(sizeof(t_bash))))
		return (NULL);
	if (!(data->env = copy_array(env)))
		return (NULL);
	data->venv = env;
	data->iterator = 0;
	data->count_separator = 0;
	data->error = NULL;
	if (!(data->vector = vect_new(NULL, NULL)))
		return (NULL);
	data->prompt_len = prompt(type);
	return (data);
}

static void		exec_vector(t_bash data)
{
	t_vect	*lst;
	char	*path;

	lst = (data.vector) ? data.vector : NULL;
	while (lst && !data.error)
	{
		if ((path = build_path(data, lst)) && !access(path, X_OK))
			exec_cmd(data, path, lst);
		else if (lst->args && !access((const char*)lst->args->content, X_OK))
			exec_cmd(data, lst->args->content, data.vector);
		else
		{
			puterror(lst->args->content);
			ft_putchar(' ');
			puterror(UNOW);
		}
		lst = lst->next;
	}
}

int		main(int argc, char **argv, char **env)
{
	t_bash	*data;

	if (argc == 1 && !conf_term())
	{
		CLEAR;
		hello();
		if (!(data = initialize_bash(env, 0)))
			puterror("c'est pas bien");
		else
			loop(data);
	}
	else if (argc > 1 && argv) // do not read file yet
	{
		if (!(data = initialize_bash(env, -1)))
			puterror("c'est pas bien");
		else
		{
			/*
			** one argv = one cmd; exec one by one ; using the same env
			*/
			for (int i = 1 ; i < argc ; i++)
			{
				data->vector->line = ft_strdup(argv[i]);
				if (!is_all_whitespaces(LINE))
				{
					format_line(data);
					exec_vector(*data);
				}
				else
					puterror("Shell is not a nudeshell\n");
				if (i + 1 != argc)
					VECT = link_history(&VECT, NULL);
			}
		}
	}
	return (0);
}
