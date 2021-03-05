/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:49:07 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:50:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	print_rest(char *str, int pos, char *old)
{
	while (str && str[pos])
	{
		ft_putchar(str[pos]);
		pos++;
	}
	if (old && pos < ft_strlen(old))
	{
		while (old[pos])
		{
			if (old[pos] == '\n')
				ft_putchar('\n');
			else
				ft_putchar(' ');
			pos++;
		}
	}
	return (pos);
}
