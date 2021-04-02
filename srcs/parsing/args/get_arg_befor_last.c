/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_befor_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:09:26 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:51:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

t_arg	*get_arg_befor_last(t_vect **current)
{
	t_arg	*args;

	args = (*current)->args;
	while (args && args->next && args->next->next)
		args = args->next;
	return (args);
}
