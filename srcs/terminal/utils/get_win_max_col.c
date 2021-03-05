/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_win_max_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:21:00 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 15:21:31 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	get_win_max_col(void)
{
	struct winsize	w;

	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
		return (w.ws_col);
	return (0);
}
