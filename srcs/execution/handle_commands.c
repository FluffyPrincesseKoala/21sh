/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:57:53 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:46:44 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** After setting fields in the command structure, handle its execution inside
**  or outside a fork.
*/

static int	handle_command(t_bash *data, t_vect *command)
{
	int		status;
	pid_t	cpid;

	unconf_term();
	select_builtin(data, command);
	if (fork_is_required(command))
	{
		cpid = fork();
		if (fork_failed(cpid))
			print_failed_fork_error(cpid);
		else if (is_child(cpid))
			if (handle_execution(data, command) == FAIL)
			{
				error_code_to_message(&data->error);
				exit(EXIT);
			}
		wait(&status);
	}
	else if (handle_execution(data, command) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/*
** Loop on each submitted command to process all steps of its execution.
** Piped commands are executed concomitantly.
*/

int			handle_commands(t_bash *data, t_vect *command)
{
	while (command)
	{
		if (is_exit(command))
			return (EXIT);
		if (handle_command(data, command) == FAIL)
			return (FAIL);
		while (command->next && command_is_piped(command))
			command = command->next;
		command = command->next;
	}
	return (SUCCESS);
}
