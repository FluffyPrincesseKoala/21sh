/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:39:40 by koala             #+#    #+#             */
/*   Updated: 2021/03/06 11:55:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

#define GOTO(X,Y)			tputs(tgoto(tgetstr("cm", NULL), X, Y), 1, &pchar)

void	hello(void)
{
	struct winsize	w;
	int				column_count;
	int				i;

	i = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	column_count = w.ws_col;
	ft_putstr(CYAN);
	ft_putstr("*");
	while (i < (column_count - 2))
	{
		ft_putchar('*');
		i++;
	}
	ft_putstr("*\n");
	ft_putstr("*");
	while (i-- > ((column_count + 5) / 2))
		ft_putchar(' ');
	ft_putstr("21SH");
	while (i++ < (column_count))
		ft_putchar(' ');
	ft_putstr("*\n");
	ft_putstr("*");
	while (i-- > 3)
		ft_putchar('*');
	ft_putstr("*\n");
	ft_putstr(RESET);
}

void	info(char *str)
{
	term_put(SAVE);
	GOTO(0, 0);
	hello();
	GOTO(0, 0);
	ft_putchar('[');
	ft_putstr(str);
	ft_putchar(']');
	term_put(RESET_C);
}

void	custom_info(int x, int y, t_term *cursor)
{
	term_put(SAVE);
	GOTO(0, 0);
	hello();
	GOTO(0, 0);
	ft_putstr("[x:");
	ft_putnbr(x);
	ft_putstr("]\t");
	ft_putstr("[y:");
	ft_putnbr(y);
	ft_putstr("]\t");
	term_put(RESET_C);
}
