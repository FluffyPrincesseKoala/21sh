/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:40:37 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:41:05 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char	*strsub_copy(char *str, int start, int size)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str || !(ret = malloc(sizeof(char) * (size - start + 1))))
		return (NULL);
	while (str[start] && start != size)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

void		select_copy(t_bash *data)
{
	if (data->is_select)
	{
		if (data->copied)
			ft_strdel(&data->copied);
		data->copied = strsub_copy(LINE, data->start_select, data->end_select);
		uncolor(data);
		unselect(data);
	}
}
