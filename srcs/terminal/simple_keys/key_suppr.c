/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_suppr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:59:03 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:59:14 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void				key_suppr(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (IDX < ft_strlen(LINE))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		tmp = delchar(LINE, IDX);
		expected = IDX;
		SAVE_C;
		print_rest(NULL, IDX, LINE);
		RESET_C;
		ft_strdel(&LINE);
		LINE = ft_strdup(tmp);
		ft_strdel(&tmp);
		print_rest(LINE, IDX, NULL);
		RESET_C;
	}
}
