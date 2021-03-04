/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:00:15 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:31:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static size_t	args_len(t_arg *arg)
{
	size_t len;

	len = 0;
	while (arg)
	{
		if (CONTENT)
			len++;
		arg = arg->next;
	}
	return (len);
}

/*
** Convert the contents of a t_arg chained list to an array of strings
*/

static char		**arg_to_array(t_bash *data, t_arg *arg)
{
	char	**array;
	int		i;

	if (!(array = malloc(sizeof(char*) * (args_len(arg) + 1))))
		data->error = MALLOC_ERROR;
	else
	{
		i = 0;
		while (arg)
		{
			if (CONTENT)
			{
				array[i] = ft_strdup(CONTENT);
				i++;
			}
			arg = arg->next;
		}
		array[i] = NULL;
	}
	return (array);
}

/*
** Find the path to the command binary file.
** Convert the args chained list to an array.
** Call execve with those parameters.
*/

static void		execute_syscall(t_bash *data, t_vect *command)
{
	ft_strdel(&(data->path));
	if (command->args
		&& (data->path = choose_command_path(data, command->args->content)))
	{
		free_array(data->args_array);
		data->args_array = arg_to_array(data, command->args);
		if (!data->error)
			execve(data->path, data->args_array, data->env);
	}
	error_code_to_message(&(data->error));
	free_bash(data);
	exit(0);
}

/*
** Execute the redirections, set up earlier, right before executing the command.
** If it's a builtin, use the appropriate custom function, otherway use execve.
*/

void			execute_command(t_bash *data, t_vect *command)
{
	if (command->redirections)
		execute_redirections(data, command, command->redirections);
	if (command->builtin)
	{
		if (!data->error)
			command->builtin(data, command);
		restore_directions(command->redirections);
	}
	else
		execute_syscall(data, command);
}
