/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_is_piped.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:18:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int	command_is_piped(t_vect *command)
{
	if (command->separator == '|')
		return (TRUE);
	else
		return (FALSE);
}
