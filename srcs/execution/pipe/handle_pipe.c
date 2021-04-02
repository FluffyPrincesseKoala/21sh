/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:05:57 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:40:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Try to open the file used in the redirection, set up resulting file
**  descriptor in the redirection structure.
*/

static int	is_file_word_authorized(
	t_bash *data, t_vect *command, t_redirection *redirection)
{
	int	new_fd;

	if (redirection->file_word)
	{
		new_fd = open(redirection->file_word, redirection->setup->flags,
				NEW_FILE_MODE);
		if (new_fd == -1)
		{
			put_error_msg("Permission non accordée: ");
			put_error_msg(redirection->file_word);
			put_error_msg("\n");
			data->error = OPEN_ERROR;
			free_redirections(command);
			return (FALSE);
		}
		else
			redirection->right_fd = new_fd;
	}
	return (TRUE);
}

static void	create_redirection_files(t_bash *data, t_vect *command)
{
	t_vect			*current_command;
	t_redirection	*current_redirection;

	current_command = command;
	while (current_command && command_is_piped(current_command))
	{
		current_redirection = current_command->redirections;
		while (current_redirection)
		{
			is_file_word_authorized(data, current_command, current_redirection);
			current_redirection = current_redirection->next;
		}
		current_command = current_command->next;
	}
	if (current_command)
	{
		current_redirection = current_command->redirections;
		while (current_redirection)
		{
			is_file_word_authorized(data, current_command, current_redirection);
			current_redirection = current_redirection->next;
		}
	}
}

/*
** Create a new redirection structure, that redirects the pipe writting file
**  descriptor to the command STDIN.
*/

static void	set_stdout_pipe_redirection(
	t_bash *data, t_vect *command, int pipe_fd[2])
{
	t_redirection	*new;

	new = new_redirection(command, TRUE);
	new->setup = data->redirect_setup[1];
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

int	handle_pipe(t_bash *data, t_vect *command)
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
		create_redirection_files(data, command);
		pipe_fork(data, command, pipe_fd, FALSE);
		if (handle_execution(data, command->next) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
