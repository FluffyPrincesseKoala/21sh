/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:12:57 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:13:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ctrl_left(t_bash *data)
{
	t_term			*curr;
	int				len;

	if (data->iterator)
	{
		while (data->iterator && ft_iswhitespace(LINE[data->iterator]))
			arrow_left(data);
		while (data->iterator && !ft_iswhitespace(LINE[data->iterator]))
			arrow_left(data);
	}
}
