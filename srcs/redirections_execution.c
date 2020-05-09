/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 22:13:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static bool is_right_fd_authorized(t_redirection *redirection)
{
	if (redirection->file_word)
	{
		new_fd = open(
			redirections->file_word, O_WRONLY | O_CREAT, NEW_FILE_MODE);
		if (new_fd == -1)
			return (false);
		else
			redirection->right_fd = new_fd;
	}
	return (true);
}

static void	get_backup_fd(t_redirection *redirection, int n)
{
	redirection->backup_fd = 600 + n;
}

bool        handle_redirections(t_redirection *redirection, int position)
{
	if (!is_right_fd_authorized(redirection)
        free_redirection(redirection);
		return (false);
	get_backup_fd(redirection, position);
	dup2(redirection->left_fd, redirection->backup_fd);
	dup2(redirection->right_fd, redirection->left_fd);
	if (redirection->file_word)
		close(redirection->file_word);
	if (redirection->next)
		return (handle_redirections(redirection->next, position+1));
	else
		return true;
}

void	    restore_directions(t_redirection *redirection)
{
	if (redirection->next)
		restore_directions(redirection->next);
	dup2(redirection->backup_fd, redirection->left_fd);
}