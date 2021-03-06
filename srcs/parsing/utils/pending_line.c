/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pending_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:45:24 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int			pending_line(char *str)
{
	char	*separator;
	int		stack;
	int		i;
	int		j;

	i = 0;
	stack = 0;
	separator = ft_strdup("\'\"");
	while (separator[i])
	{
		j = -1;
		while (str && str[++j])
		{
			if (str[j] == separator[i] && ((j && str[j - 1] != '\\')
			|| (j >= 2 && str[j - 1] == '\\' && str[j - 2] == '\\') || (!j)))
				stack += (stack) ? 1 : -1;
		}
		if (stack)
			break ;
		i++;
	}
	ft_strdel(&separator);
	return (stack);
}
