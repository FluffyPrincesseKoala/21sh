/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/25 16:26:35 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions related to heredoc pipes at execution time.
*/

/*
**	Print the doc string line by line in the pipe file descriptor.
*/

void		write_heredoc(t_bash *data, t_vect *command, int pipe_fd[2])
{
	int i;

	i = 0;
	while ((command->doc_string)[i])
	{
		if (ft_strcmp(command->doc_string[i], command->eof))
		{
			write(pipe_fd[1], (command->doc_string)[i], ft_strlen((command->doc_string)[i]));
			write(pipe_fd[1], "\n", 1);
		}
		i++;
	}
	
}

/*
** Create a pipe, redirect pipe reading file descriptor to the command STDIN.
** Fork the current process, write the heredoc in the child and execute the 
**  command in the parent.
*/

void		handle_heredoc(t_bash *data, t_vect *command)
{
	int		pipe_fd[2];


    if (using_heredoc(command))
	{
		if (pipe(pipe_fd) == EXIT)
			exit(EXIT);
		set_stdin_pipe_redirection(command, pipe_fd);
		pipe_fork(data, command, pipe_fd, TRUE);
	}
}
