/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stdin_pipe_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:41:12 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Create a new redirection structure, that redirects the pipe reading file
**  descriptor to the command STDOUT.
*/

void	set_stdin_pipe_redirection(t_bash *data, t_vect *cmd, int pipe_fd[2])
{
	t_redirection	*new;

	new = new_redirection(cmd, FALSE);
	new->setup = data->redirect_setup[2];
	new->left_fd = 0;
	new->right_fd = pipe_fd[0];
}
