/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:27:52 by koala             #+#    #+#             */
/*   Updated: 2021/01/22 12:48:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void		put_error_msg(char *error)
{
	if (error)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd(error, STDERR);
		ft_putstr_fd(RESET, STDERR);
	}
}

void		puterror(int error)
{
	ft_putstr_fd(RED, STDERR);
	ft_putnbr_fd(error, STDERR);
	ft_putstr_fd(RESET, STDERR);
}

void		print_failed_fork_error(pid_t pid)
{
	ft_putstr_fd("fork failed at ", 2);
	ft_putnbr_fd((int)pid, 2);
	ft_putchar('\n');
	exit(-1);
}
