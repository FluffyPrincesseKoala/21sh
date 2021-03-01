/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/01 18:19:49 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int  is_non_escaped_quote(const char *s, char quote, int i)
{    
    if (s[i] == quote && (i == 0 || (s[i - 1] != '\\' || (i > 1 && s[i - 2] == '\\'))))
        return (TRUE);
    else
        return (FALSE);
}

char		*unquote(char *line_substr, char quote)
{
	size_t	len;

	len = 1;
	while (line_substr[len] && !is_non_escaped_quote(line_substr, quote, len))
		len++;
	return ft_strsub(line_substr, 1, len - 1);
}