/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:57:53 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:58:09 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	is_exit(t_vect *command)
{
	if (command->args && ft_strequ(command->args->content, "exit"))
		return (TRUE);
	return (FALSE);
}

static int	fork_is_required(t_vect *command)
{
	if (command->builtin && !command_is_piped(command))
		return (FALSE);
	else
		return (TRUE);
}

/*
** If the arg match a builtin command, add it to the current command structure
*/

static void	select_builtin(t_bash *data, t_vect *command)
{
	int	i;

	i = 0;
	while (i != NB_BUILTIN)
	{
		if (command->args
			&& ft_strequ(command->args->content, data->builtin[i].name))
			command->builtin = data->builtin[i].f;
		i++;
	}
}

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
		check_failed_fork(cpid);
		if (is_child(cpid))
		{
			if (handle_execution(data, command) == FAIL)
			{
				error_code_to_message(&data->error);
				exit(EXIT);
			}
		}
		signal(SIGINT, SIG_IGN);
		wait(&status);
		setup_signals(0);
		g_data->started = FALSE;
	}
	else if (handle_execution(data, command) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/*
** Loop on each submitted command to process all steps of its execution.
** Piped commands are executed concomitantly.
*/

int	handle_commands(t_bash *data, t_vect *command)
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
