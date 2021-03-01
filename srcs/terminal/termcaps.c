/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:15:56 by koala             #+#    #+#             */
/*   Updated: 2021/01/06 17:40:04 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	term_put(char *esc)
{
	char	*caps;
	char	*term;

	term = NULL;
	caps = tgetstr(esc, NULL);
	if (!ft_strequ(esc, "cl"))
		term = tgoto(caps, 0 , 0);
	tputs((term) ? term : caps, 1, &pchar);
}
