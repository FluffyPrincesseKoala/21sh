/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:44:18 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/10 17:26:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	pstr(char const *str)
{
	if (str)
		return (write(1, str, ft_strlen((char *)str)));
	return (0);
}

int			prompt(char **env, int short_prompt)
{
	char	*value;
	int		len;

	len = 0;
	if (!short_prompt)
	{
		pstr(BLUE);
		len += pstr(get_value_from_env(env, "USER"));
		pstr(RESET);
		len += pchar('@');
		pstr(GREEN);
		len += pstr(get_value_from_env(env, "PWD"));
		pstr(CYAN);
		len += pstr(" > ");
	}
	else
	{
		if (short_prompt == -1)
		{
			pstr(BACK_BLUE);
			len += pstr("Heredoc");
		}
		pstr(CYAN);
		len += pstr(" > ");
	}
	pstr(RESET);
	return (len);
}
