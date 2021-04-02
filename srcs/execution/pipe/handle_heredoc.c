/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:03:22 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:39:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	using_heredoc(t_vect *command)
{
	if (command->doc_string != NULL)
	{
		return (TRUE);
	}
	else
		return (FALSE);
}

/*
** Create a pipe, redirect pipe reading file descriptor to the command STDIN.
** Fork the current process, write the heredoc in the child and execute the
**  command in the parent.
*/

void	handle_heredoc(t_bash *data, t_vect *command)
{
	int	pipe_fd[2];

	if (using_heredoc(command))
	{
		if (pipe(pipe_fd) == EXIT)
			exit(EXIT);
		set_stdin_pipe_redirection(data, command, pipe_fd);
		pipe_fork(data, command, pipe_fd, TRUE);
	}
}
