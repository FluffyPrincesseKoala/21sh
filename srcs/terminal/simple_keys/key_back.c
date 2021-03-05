/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:25:25 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:25:40 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	key_back(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (IDX && ft_strlen(LINE))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		tmp = delchar(LINE, IDX - 1);
		expected = IDX - 1;
		arrow_left(data);
		old = ft_strdup(LINE);
		ft_strdel(&LINE);
		LINE = ft_strdup(tmp);
		SAVE_C;
		print_rest(NULL, IDX, old);
		RESET_C;
		print_rest(LINE, IDX, NULL);
		RESET_C;
		ft_strdel(&old);
		ft_strdel(&tmp);
	}
}
