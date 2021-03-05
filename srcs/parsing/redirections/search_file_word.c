/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:48:46 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:51:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** Take a look at the right of the redirection operator.
** If any word is present, return a copy of it.
** Else, look for it in the next argument.
** If the redirection operator is the end of the command, that's an error.
*/

char	*search_file_word(
	t_vect *cmd, t_arg *arg, int substring_index, int *error)
{
	char	*file;

	file = NULL;
	if (substring_index != ft_strlen(CONTENT))
	{
		if (!(file = ft_strsub(CONTENT,
			substring_index, ft_strlen(CONTENT) - substring_index)))
			*error = MALLOC_ERROR;
	}
	else if (arg->next && arg->next->content)
	{
		if (!(file = ft_strdup(arg->next->content)))
			*error = MALLOC_ERROR;
		del_one_arg(arg->next, cmd);
	}
	else
		*error = UNEXPECT_COMMAND_END_ERROR;
	return (file);
}
