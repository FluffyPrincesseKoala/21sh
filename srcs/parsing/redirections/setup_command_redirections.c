/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_command_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:36:21 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/08 12:38:43 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** Search for redirections in the given command.
** Whe it finds one, call the appropriate set up function and remove the
**  concerned argument.
** Loop the function on the next command.
*/

int	setup_command_redirections(t_bash *data, t_vect *command)
{
	t_redirection	*redirection;

	redirection = command->redirections;
	while (redirection)
	{
		if (redirection->arg)
		{
			redirection->setup->f(command, redirection->arg,
				redirection, &(data->error));
			del_one_arg(redirection->arg, command);
		}
		else
			redirection = redirection->next;
		if (data->error)
			return (FAIL);
		if (redirection)
			redirection = redirection->next;
	}
	return (SUCCESS);
}
