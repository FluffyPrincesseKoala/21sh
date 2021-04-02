/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_failed_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 18:19:07 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/02 19:45:46 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	check_failed_fork(pid_t pid)
{
	if (pid < 0)
	{
		ft_putstr_fd("fork failed at ", 2);
		ft_putnbr_fd((int)pid, 2);
		ft_putchar('\n');
		exit(-1);
	}
}
