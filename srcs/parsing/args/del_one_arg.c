/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_one_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:41:54 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:35:39 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	del_one_arg(t_arg *arg, t_vect *cmd)
{
	detach_arg(arg, cmd);
	ft_strdel(&arg->content);
	free(arg);
	arg = NULL;
}
