/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_stdout_and_stderr_redirection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:49:39 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:47:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** Redirections in the form &>word or >&word or &>>word indicated that both
**  STDIN and STDERR are redirected to the given word.
** This function return true if the redirection concerns both STDIN and STDERR.
*/

int	is_stdout_and_stderr_redirection(int left_fd, int right_fd)
{
	if (left_fd == STDOUT_AND_STDERR && right_fd == NO_RIGHT_FD)
		return (TRUE);
	else if (left_fd == STDOUT && right_fd == AMBIGUOUS)
		return (TRUE);
	else
		return (FALSE);
}
