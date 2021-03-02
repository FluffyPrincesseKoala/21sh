/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:40:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
**	Print the doc string line by line in the pipe file descriptor.
*/

void	write_heredoc(t_bash *data, t_vect *cmd, int pipe_fd[2])
{
	int	i;

	i = 0;
	while ((cmd->doc_string)[i])
	{
		if (ft_strcmp(cmd->doc_string[i], cmd->eof))
		{
			write(pipe_fd[1],
				(cmd->doc_string)[i],
				ft_strlen((cmd->doc_string)[i]));
			write(pipe_fd[1], "\n", 1);
		}
		i++;
	}
}
