/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unselect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:39:41 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	unselect(t_bash *data)
{
	data->is_select = 0;
	data->end_select = 0;
	data->start_select = 0;
	data->select_direction = 0;
}
