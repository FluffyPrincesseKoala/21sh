/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:12:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:12:43 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ctrl_right(t_bash *data)
{
	t_term			*curr;
	int				len;

	if (data->iterator < (len = ft_strlen(LINE)))
	{
		while (data->iterator < len && ft_iswhitespace(LINE[data->iterator]))
			arrow_right(data);
		while (data->iterator < len && !ft_iswhitespace(LINE[data->iterator]))
			arrow_right(data);
	}
}
