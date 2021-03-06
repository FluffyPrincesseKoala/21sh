/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_escaped_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:37:05 by koala             #+#    #+#             */
/*   Updated: 2021/03/06 17:55:46 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int	is_non_escaped_quote(const char *s, char quote, int i)
{
	if (s[i] == quote
		&& (i == 0 || (s[i - 1] != '\\' || (i > 1 && s[i - 2] == '\\'))))
		return (TRUE);
	else
		return (FALSE);
}
