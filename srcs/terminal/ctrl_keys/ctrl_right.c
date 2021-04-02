/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:12:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:04:09 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	ctrl_right(t_bash *data)
{
	t_term	*curr;
	int		len;

	len = ft_strlen(data->vector->line);
	if (data->iterator < len)
	{
		while (data->iterator < len
			&& ft_iswhitespace(data->vector->line[data->iterator]))
			arrow_right(data);
		while (data->iterator < len
			&& !ft_iswhitespace(data->vector->line[data->iterator]))
			arrow_right(data);
	}
}
