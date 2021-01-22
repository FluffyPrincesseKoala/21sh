/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:23:17 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/15 12:23:45 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	print_args(t_bash *data, t_vect *command)
{
	command->args = command->args->next;
	while (command->args)
	{
		ft_putstr(command->args->content);
		if (command->args->next)
			ft_putchar(' ');
		command->args = command->args->next;
	}
	ft_putchar('\n');
}

static void	init_built_in(t_built **fct)
{
	if (!(*fct = ft_memalloc(sizeof(t_built) * NB_BUILTIN)))
		return ;
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
}
//			print_history(data);
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

int 	    check_built_in(t_bash *data, t_vect *command)
{
	int 	i;
	int 	exit;

	i = 0;
	exit = 0;
	if (!data->builtin)
		init_built_in(&data->builtin);
    if (ft_strnequ(command->args->content, "exit", 4))
		return (-1);
	while (i != NB_BUILTIN && !exit)
	{
		if (ft_strnequ(command->args->content, data->builtin[i].name, data->builtin[i].len))
		{
			if (command->redirections)
				handle_redirections(data, command->redirections, 0);
			data->builtin[i].f(data, command);
			if (command->redirections)
				restore_directions(command->redirections);
			return (1);
		}
		i++;
	}
    return (0);
}