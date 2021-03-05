/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:55:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 18:58:22 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		put_error_msg(char *error)
{
	if (error)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd(error, STDERR);
		ft_putstr_fd(RESET, STDERR);
	}
}