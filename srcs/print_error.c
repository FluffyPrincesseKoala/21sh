/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:27:52 by koala             #+#    #+#             */
/*   Updated: 2020/12/14 15:28:10 by koala            ###   ########.fr       */
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
