/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/15 18:54:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void        set_child_pipe_redirection(t_vect *command, int pipe_fd[2])
{
	t_redirection *new;
    
	new = new_redirection(command, 0);
	new->left_fd = 0;
	new->right_fd = pipe_fd[0];
}

void		set_pipe_redirection(t_vect *command, int pipe_fd[2])
{
	t_redirection *new;

	new = new_redirection(command, 0);
	new->left_fd = 1;
	new->right_fd = pipe_fd[1];
    set_child_pipe_redirection(command->next, pipe_fd);
}

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

void		handle_pipe(t_bash *data, t_vect *command)
{
	int				pipe_fd[2];

	if (command_is_piped(command))
	{
		if (pipe(pipe_fd) == EXIT)
            exit(EXIT);
		set_pipe_redirection(command, pipe_fd);
		pipe_fork(data, command, pipe_fd, FALSE);
		handle_execution(data, command->next);
	}
	
}