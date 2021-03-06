/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:11:14 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Use a backup file director to reverse the initial dup.
** Recursively call the function on the next redirection
*/

void	restore_directions(t_redirection *redirection)
{
	if (redirection)
	{
		if (redirection->next)
			restore_directions(redirection->next);
		close(redirection->left_fd);
		dup2(redirection->backup_fd, redirection->left_fd);
	}
}
