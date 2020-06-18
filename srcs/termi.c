/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:25:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/11 19:10:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int					print_rest(char *str, int pos, char *old)
{
	while (str && str[pos])
	{
		ft_putchar(str[pos]);
		pos++;
	}
	if (old && pos < ft_strlen(old))
	{
		while (old[pos])
		{
			if (old[pos] == '\n')
				ft_putchar('\n');
			else
				ft_putchar(' ');
			pos++;
		}
	}
	return (pos);
}

/*
**	add function ptr like that "void (*f)()"
*/

void				ctrl_right(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				len;

	len = data->iterator;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	while (data->vector->line[len] && data->vector->line[len] == ' ')
		len++;
	while (data->vector->line[len] && data->vector->line[len] != ' ')
		len++;
	while (data->iterator != len)
	{
		y = (data->iterator + data->prompt_len) / w.ws_col;
		x = (data->iterator + data->prompt_len) % w.ws_col;
		if (x == w.ws_col - 1)
			CDOWN;
		else
			RIGHT;
		data->iterator++;		
	}
}

void				ctrl_left(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				len;

	if ((len = data->iterator) && ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
		len--;
	while (len && data->vector->line[len] == ' ')
		len--;
	while (len && data->vector->line[len] != ' ')
		len--;
	while (data->iterator != len)
	{
		y = (data->iterator + data->prompt_len) / w.ws_col;
		x = (data->iterator + data->prompt_len) % w.ws_col;
		if (!x && y)
		{
			UP;
			while (x++ != w.ws_col)
				RIGHT;
		}
		else
			LEFT;
		(*data).iterator--;
	}
}

void				ctrl_down(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				expected;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!data->expend)
	{
		init_xy(data, &x, &y, w.ws_col);
		expected = y + 1;
		while (y != expected && data->iterator < ft_strlen(LINE))
		{
			init_xy(data, &x, &y, w.ws_col);
			arrow_right(data);
		}
	}
}

void				ctrl_up(t_bash *data)
{
	struct winsize	w;
	int				y;
	int				x;
	int				expected;


	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	init_xy(data, &x, &y, w.ws_col);
	if (y && !data->expend)
	{
		expected = y - 1;
		while (y != expected)
		{
			init_xy(data, &x, &y, w.ws_col);
			arrow_left(data);
		}
	}
}

void		arrow_key(t_bash *data, char *buff)
{
	if (ft_strnequ(buff, "\033[A", 3))
		arrow_up(data);
	else if (ft_strnequ(buff, "\033[B", 3))
		arrow_down(data);
	else if (ft_strnequ(buff, "\033[C", 3))
		arrow_right(data);
	else if (ft_strnequ(buff, "\033[D", 3))
		arrow_left(data);
	else if (ft_strnequ(buff, "\033[3~", 4))
		key_suppr(data);
	else if (buff[0] == 127)
		key_back(data);
	else if (ft_strnequ(buff, "\033[1;5D", 6) && data->iterator)
		ctrl_left(data);
	else if (ft_strnequ(buff, "\033[1;5C", 6))
		ctrl_right(data);
	else if (ft_strnequ(buff, "\033[1;5B", 6))
		ctrl_down(data);
	else if (ft_strnequ(buff, "\033[1;5A", 6))
		ctrl_up(data);		
	else if (ft_strnequ(buff, "\033[H", 3))
		key_start(data);
	else if (ft_strnequ(buff, "\033[F", 3))
		key_last(data);
}
