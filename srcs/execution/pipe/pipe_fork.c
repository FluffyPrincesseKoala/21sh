/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:08:37 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:58:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Fork the current process.
** In the child close the reading pipe file director and write the docstring if
**  it's a heredoc situation or execute the current command.
** The parent wait for the child process, then close the writting pipe file
**  director.
*/

void	pipe_fork(t_bash *data, t_vect *command, int pipe_fd[2], int heredoc)
{
	int		status;
	pid_t	cpid;

	cpid = fork();
	check_failed_fork(cpid);
	if (is_child(cpid))
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
	g_data->started = FALSE;
	setup_signals(0);
	close(pipe_fd[1]);
}
