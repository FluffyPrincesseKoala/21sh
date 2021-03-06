/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_right_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:47:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Take a look at the right of the redirection operator.
** If there is no '&' this means there is no file director here.
** If there are digits only after the '&', set them as file director.
** If there is a '-' after the '&', this means the left file director needs to
**  be closed, if there still a word the '-', considers it as a detached
**  argument and add it to the command argument list.
** If there any other kind of word right after '&', this means there might be an
**  ambiguous syntax in the submitted command.
*/

int	search_right_fd(t_vect *cmd, t_arg *arg, char *substring, int *error)
{
	if (substring[0] == '&')
	{
		if (substring[1] && ft_str_is_digits(&(substring[1])))
			return (ft_atoi(&(substring[1])));
		else if (substring[1] == CLOSE_DIRECTION)
		{
			if (ft_strlen(substring) != 2)
			{
				if (!insert_new_arg(cmd, arg,
					ft_strsub(substring, 2, ft_strlen(substring) - 2)))
					*error = MALLOC_ERROR;
			}
			return (CLOSE_FD);
		}
		else
			return (AMBIGUOUS);
	}
	return (NO_RIGHT_FD);
}
