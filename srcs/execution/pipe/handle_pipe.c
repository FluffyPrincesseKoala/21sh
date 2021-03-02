/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:05:57 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:38:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** Create a new redirection structure, that redirects the pipe writting file
**  descriptor to the command STDIN.
*/

static void	set_stdout_pipe_redirection(
	t_bash *data, t_vect *command, int pipe_fd[2])
{
	t_redirection *new;

	new = new_redirection(command);
	new->setup = data->redirections_setup[1];
	new->left_fd = 1;
	new->right_fd = pipe_fd[1];
}

/*
** Create the redirections structure for the pipe between the current command
**  and the next one.
** Fork the current process, and execute the current command in the child.
** Then, handle the execution of the next command, after parsing it for
**  potential redirections.
*/

int			handle_pipe(t_bash *data, t_vect *command)
{
	int	pipe_fd[2];

	if (command_is_piped(command))
	{
		if (!command->next || !command->next->args)
		{
			data->error = UNEXPECT_COMMAND_END_ERROR;
			return (FAIL);
		}
		if (pipe(pipe_fd) == EXIT)
			exit(EXIT);
		set_stdout_pipe_redirection(data, command, pipe_fd);
		set_stdin_pipe_redirection(data, command->next, pipe_fd);
		pipe_fork(data, command, pipe_fd, FALSE);
		if (handle_execution(data, command->next) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
