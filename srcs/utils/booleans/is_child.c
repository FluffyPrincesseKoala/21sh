/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:19:41 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

int	is_child(pid_t pid)
{
	if (pid == 0)
		return (TRUE);
	else
		return (FALSE);
}
