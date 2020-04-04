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

bool        create_redirection(t_vect *cmd)
{
    t_redirection   *new;
    t_redirection   *cursor;

    if (!new = ft_memalloc(sizeof(t_redirection)))
        return false;
    if (cmd->redirection)
    {
        cursor = cmd->redirection;
        while (cursor->next)
            cursor = cursor->next;
        cursor->next = new;
    }
    else
        cmd->redirection = new;
}

void        free_redirection(t_redirection *redirection)
{
    if (redirection->next)
        free_redirection(redirection->next);
    redirection->next = NULL;
    ft_strdel(opened_file);
    free(redirection);
}

static bool is_out_fd_authorized(t_redirection *redirection)
{
	if (permission->opened_file)
	{
		new_fd = open(
			redirections->opened_file, O_WRONLY | O_CREAT, NEW_FILE_MODE);
		if (new_fd == -1)
			return (false);
		else
			redirection->out_fd = new_fd;
	}
	return (true);
}

static void	get_backup_fd(t_redirection *redirection, int n)
{
	redirection->backup_fd = 600 + n;
}

bool        handle_redirections(t_redirection *redirection, int position)
{
	if (!is_out_fd_authorized(redirection)
        free_redirection(redirection);
		return (false);
	get_backup_fd(redirection, position);
	dup2(redirection->in_fd, redirection->backup_fd);
	dup2(redirection->out_fd, redirection->in_fd);
	if (redirection->opened_file)
		close(redirection->opened_file);
	if (redirection->next)
		return (handle_redirections(redirection->next, position+1));
	else
		return true;
}

void	    restore_directions(t_redirection *redirection)
{
	if (redirection->next)
		restore_directions(redirection->next);
	dup2(redirection->backup_fd, redirection->in_fd);
}