/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:29:41 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** This file contains functions related to redirection chained list manipulation
*/

/*
** Free the whole redirections chained list.
*/

static void	free_redirection(t_redirection *redirection)
{
	if (redirection->next)
		free_redirection(redirection->next);
	redirection->next = NULL;
	ft_strdel(&redirection->file_word);
	free(redirection);
}

/*
** Free the whole redirections chained list, set pointers to null.
*/

void	free_redirections(t_vect *command)
{
	if (command->redirections)
		free_redirection(command->redirections);
	command->redirections = NULL;
}
