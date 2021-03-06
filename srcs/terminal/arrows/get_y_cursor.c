/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_y_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:03:32 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int	get_y_cursor(t_term *src)
{
	int				count;

	count = 0;
	while (src->prev)
	{
		src = src->prev;
		count += 1;
	}
	return (count);
}
