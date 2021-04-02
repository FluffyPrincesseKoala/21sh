/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pending_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:45:24 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:22:41 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int	pending_line(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str && str[i])
	{
		quote = is_quote(str[i++]);
		if (quote)
		{
			while (str[i] && !is_non_escaped_quote(str, quote, i))
				i++;
			if (!str[i])
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}
