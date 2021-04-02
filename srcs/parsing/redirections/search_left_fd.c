/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_left_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:46:14 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:26:58 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Take a look at the left of the redirection operator.
** If there is nothing, just send the given default file director.
** If there are digits only, set them as file director.
** If there is a '&', it means the redirection concerns both STDOUT and STDERR.
** Else it considers any present word as a detached argument and add it to the
**  command argument list.
*/

int	search_left_fd(t_vect *cmd, t_arg *arg, int operator_idx, int *error)
{
	char	*substring;
	int		return_value;

	return_value = NO_LEFT_FD;
	if (operator_idx > 0)
	{
		substring = ft_strsub(arg->content, 0, operator_idx);
		if (!substring)
			*error = MALLOC_ERROR;
		else if (ft_str_is_digits(substring))
			return_value = ft_atoi(substring);
		else if (ft_strlen(substring) == 1 && substring[0] == '&')
			return_value = (STDOUT_AND_STDERR);
		else
		{
			if (insert_new_arg(
					cmd, arg->previous, ft_strdup(substring)) == FAIL)
				*error = MALLOC_ERROR;
		}
		ft_strdel(&substring);
	}
	return (return_value);
}
