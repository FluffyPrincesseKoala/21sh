/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:53:23 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:30:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void			parse_var(t_arg *arg, char **env)
{
	char	*tmp;

	if (arg->content && ft_strchr(arg->content, '$'))
	{
		tmp = use_shell_var(env, arg->content);
		ft_strdel(&arg->content);
		arg->content = tmp;
	}
}
