/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_one_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:41:54 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/08 20:15:23 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	del_one_arg(t_arg *arg, t_vect *cmd)
{
	detach_arg(arg, cmd);
	ft_strdel(&arg->content);
	ft_strdel(&arg->quoted);
	free(arg);
	arg = NULL;
}
