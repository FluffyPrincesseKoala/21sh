/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:15:56 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	term_put(char *esc)
{
	char	*caps;
	char	*term;

	term = NULL;
	caps = tgetstr(esc, NULL);
	if (!ft_strequ(esc, "cl"))
		term = tgoto(caps, 0, 0);
	tputs((term) ? term : caps, 1, &pchar);
}
