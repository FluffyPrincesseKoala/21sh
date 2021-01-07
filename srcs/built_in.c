/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:23:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/12/18 13:31:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	print_args(t_bash *data, t_vect *command)
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
	if (!(*fct = ft_memalloc(sizeof(t_built) * 4)))
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
}

int 	    check_built_in(t_bash *data, t_vect *command)
{
	static t_built	*fct;
	int 	i;
	int 	exit;
	int		status;

	i = 0;
	exit = 0;
	if (!fct)
		init_built_in(&fct);
    if (ft_strnequ(command->args->content, "exit", 4))
		return (-1);
	while (i != 4 && !exit)
	{
		if (ft_strnequ(command->args->content, fct[i].name, fct[i].len))
		{
			if (command->separator == '|')
				handle_pipe(data, command);
			if (command->redirections)
				handle_redirections(data, command->redirections, 0);
			fct[i].f(data, command);
			if (command->redirections)
				restore_directions(command->redirections);
			wait(&status);
			return (1);
		}
		i++;
	}
    return (0);
}