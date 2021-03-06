/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Try to open the file used in the redirection, set up resulting file
**  descriptor in the redirection structure.
*/

static int	is_file_word_authorized(
	t_bash *data, t_vect *command, t_redirection *redirection)
{
	int new_fd;

	if (redirection->file_word)
	{
		new_fd = open(
			redirection->file_word, redirection->setup->flags, NEW_FILE_MODE);
		if (new_fd == -1)
		{
			put_error_msg("Permission non accordée: ");
			put_error_msg(redirection->file_word);
			put_error_msg("\n");
			data->error = OPEN_ERROR;
			free_redirections(command);
			return (FALSE);
		}
		else
			redirection->right_fd = new_fd;
	}
	return (TRUE);
}

/*
** Open file if file given.
** Make a backup of the file descriptor that is going to be overwritten.
** Apply the required redirection.
** Recursively call the function on the next redirection.
*/

int			execute_redirections(
	t_bash *data, t_vect *command, t_redirection *redirection)
{
	if (!is_file_word_authorized(data, command, redirection))
		return (FAIL);
	redirection->backup_fd = dup(redirection->left_fd);
	if (redirection->right_fd == CLOSE_FD)
		close(redirection->left_fd);
	else
	{
		dup2(redirection->right_fd, redirection->left_fd);
		if (redirection->file_word)
			close(redirection->right_fd);
	}
	if (redirection->next)
		return (execute_redirections(data, command, redirection->next));
	return (SUCCESS);
}
