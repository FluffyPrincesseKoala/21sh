/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/25 16:26:39 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions related to commands execution with a pipe.
*/

/*
** Create a new redirection structure, that redirects the pipe writting file
**  descriptor to the command STDIN.
*/

static void	set_stdout_pipe_redirection(t_vect *command, int pipe_fd[2])
{
	t_redirection *new;

	new = new_redirection(command, 0);
	new->left_fd = 1;
	new->right_fd = pipe_fd[1];
}

/*
** Create a new redirection structure, that redirects the pipe reading file
**  descriptor to the command STDOUT.
*/

void        set_stdin_pipe_redirection(t_vect *command, int pipe_fd[2])
{
	t_redirection *new;
    
	new = new_redirection(command, 0);
	new->left_fd = 0;
	new->right_fd = pipe_fd[0];
}

/*
** Fork the current process.
** In the child close the reading pipe file director and write the docstring if
**  it's a heredoc situation or execute the current command.
** The parent wait for the child process, then close the writting pipe file
**  director.
*/

void        pipe_fork(t_bash *data, t_vect *command, int pipe_fd[2], int heredoc)
{
	int status;
    pid_t cpid;

	cpid = fork();
	if (fork_failed(cpid))
		print_failed_fork_error(cpid);
	else if (is_child(cpid))
	{
		close(pipe_fd[0]);
		if (heredoc == TRUE)
			write_heredoc(data, command, pipe_fd);
		else
		{
    		handle_heredoc(data, command);
    		execute_command(data, command);
		}
		exit(0);
	}
	wait(&status);
	close(pipe_fd[1]);
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
	int				pipe_fd[2];

	if (command_is_piped(command))
	{
		if (!command->next || !command->next->args)
		{
			data->error = UNEXPECT_COMMAND_END_ERROR;
			return (FAIL);
		}
		if (pipe(pipe_fd) == EXIT)
            exit(EXIT);
		set_stdout_pipe_redirection(command, pipe_fd);
		set_stdin_pipe_redirection(command->next, pipe_fd);
		pipe_fork(data, command, pipe_fd, FALSE);
		if (set_up_command_redirections(data, command->next) == FAIL)
			return (FAIL);
		if (handle_execution(data, command->next) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}