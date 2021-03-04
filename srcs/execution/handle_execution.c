/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:59:33 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:45:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	handle_execution(t_bash *data, t_vect *command)
{
	if (handle_pipe(data, command) == FAIL)
		return (FAIL);
	handle_heredoc(data, command);
	execute_command(data, command);
	return (SUCCESS);
}
