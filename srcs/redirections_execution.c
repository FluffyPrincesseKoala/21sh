/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:12:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/12/18 13:41:46 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	is_file_word_authorized(t_bash *data, t_redirection *redirection)
{
	int new_fd;

	if (redirection->file_word)
	{
		new_fd = open(
			redirection->file_word, redirection->flags, NEW_FILE_MODE);
		if (new_fd == -1)
		{
			data->error = OPEN_ERROR;
			free_redirection(redirection);
			return (FALSE);
		}
		else
			redirection->right_fd = new_fd;
	}
	return (TRUE);
}

static void	get_backup_fd(t_redirection *redirection, int n)
{
	redirection->backup_fd = 600 + n;
}

void        handle_redirections(t_bash *data, t_redirection *redirection, int position)
{
	// take CLOSE_FD (== -1) into account
	if (!is_file_word_authorized(data, redirection))
		return ;
	ft_putstr("copy fd ");ft_putnbr(redirection->right_fd);ft_putstr(" into ");ft_putnbr(redirection->left_fd);ft_putchar('\n');
	get_backup_fd(redirection, position);
	dup2(redirection->left_fd, redirection->backup_fd);
	if (redirection->right_fd == CLOSE_FD)
		close(redirection->left_fd);
	else 
	{
		dup2(redirection->right_fd, redirection->left_fd);
		if (redirection->file_word)
			close(redirection->right_fd);
	}
	if (redirection->next)
		handle_redirections(data, redirection->next, position+1);
}

void	    restore_directions(t_redirection *redirection)
{
	if (redirection->next)
		restore_directions(redirection->next);
	close(redirection->left_fd);
	dup2(redirection->backup_fd, redirection->left_fd);
}
