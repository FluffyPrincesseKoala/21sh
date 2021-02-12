/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 12:55:29 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions related to the execution of the redirections.
*/

/*
** Try to open the file used in the redirection, set up resulting file 
**  descriptor in the redirection structure.
*/

static int	is_file_word_authorized(t_bash *data, t_redirection *redirection)
{
	int new_fd;

	if (redirection->file_word)
	{
		new_fd = open(
			redirection->file_word, redirection->flags, NEW_FILE_MODE);
		if (new_fd == -1)
		{
			put_error_msg("Permission non accordée.\n");
			data->error = OPEN_ERROR;
			free_redirection(redirection);
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

int        execute_redirections(t_bash *data, t_redirection *redirection)
{
	if (!is_file_word_authorized(data, redirection))
		return (FAIL);
	redirection->backup_fd = dup(redirection->left_fd);
	if (redirection->right_fd == CLOSE_FD)
		close(redirection->left_fd);
	else 
	{
		//ft_putstr_fd("copy ", 2);ft_putnbr_fd(redirection->right_fd, 2);ft_putstr_fd(" into ", 2);ft_putnbr_fd(redirection->left_fd, 2);ft_putchar_fd('\n', 2);
		dup2(redirection->right_fd, redirection->left_fd);
		if (redirection->file_word)
			close(redirection->right_fd);
	}
	if (redirection->next)
		return (execute_redirections(data, redirection->next));
	return (SUCCESS);
}

/*
** Use a backup file director to reverse the initial dup.
** Recursively call the function on the next redirection
*/

void	    restore_directions(t_redirection *redirection)
{
	if (redirection)
	{
		if (redirection->next)
			restore_directions(redirection->next);
		close(redirection->left_fd);
		dup2(redirection->backup_fd, redirection->left_fd);
	}
}
