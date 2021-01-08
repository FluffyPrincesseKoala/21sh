/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/08 18:29:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

//void		handle_pipe(t_bash *data, t_vect *command)
//{
//	char			**args_array;
//	char			*path;
//	int				pipe_fd[2];
//	pid_t			cpid;
//    t_redirection   *new;
//
//	pipe(pipe_fd);
//	cpid = fork();
//	if (fork_failed(cpid))
//		print_failed_fork_error(cpid);
//	else if (is_child(cpid))
//	{
//		close(pipe_fd[1]);
//		command = command->next;
//		args_array = arg_to_array(data, command->args);
//		new = new_redirection(command, 0);
//		new->left_fd = 0;
//		new->right_fd = pipe_fd[0];
//		if (check_built_in(data, command) == 0)
//			if (!data->error)
//				if ((path = choose_path(*args_array, command, data)))
//					execute_command(data, command, args_array, path);
//		exit(-1);
//	}
//	else
//	{
//		close(pipe_fd[0]);
//		new = new_redirection(command, 0);
//		new->left_fd = 1;
//		new->right_fd = pipe_fd[1];
//	}
//}

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

void        pipe_fork(t_bash *data, t_vect *command, int pipe_fd[2])
{
    pid_t cpid;

	cpid = fork();
	if (fork_failed(cpid))
		print_failed_fork_error(cpid);
	else if (is_child(cpid))
	{
		close(pipe_fd[1]);
        if (using_heredoc)
            execute_command(data, command);
        else
    		new_handle_command(data, command, TRUE);
		exit(-1);
	}
	close(pipe_fd[0]);
}

void		handle_pipe(t_bash *data, t_vect *command)
{
	int				pipe_fd[2];

	if (command_is_piped(command))
	{
		if (pipe(pipe_fd) == EXIT)
            exit(EXIT);
		set_pipe_redirection(command, pipe_fd);
		pipe_fork(data, command->next, pipe_fd);
	}
}