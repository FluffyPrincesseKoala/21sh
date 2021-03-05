/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:39:40 by koala             #+#    #+#             */
/*   Updated: 2020/12/10 15:39:41 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	info(char *str)
{
	SAVE_C;
	GOTO(0, 0);
	hello();
	GOTO(0, 0);
	ft_putchar('[');
	ft_putstr(str);
	ft_putchar(']');
	RESET_C;
}

void	custom_info(int x, int y, t_term *cursor)
{
	SAVE_C;
	GOTO(0, 0);
	hello();
	GOTO(0, 0);
	ft_putstr("[x:");
	ft_putnbr(x);
	ft_putstr("]\t");
	ft_putstr("[y:");
	ft_putnbr(y);
	ft_putstr("]\t");
	RESET_C;
}
