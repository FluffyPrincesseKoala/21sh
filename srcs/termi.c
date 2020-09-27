/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:25:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/27 02:46:24 by cylemair         ###   ########.fr       */
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
			{
				info("SHIT");
				ft_putchar('\n');
			}
			else
				ft_putchar(' ');
			pos++;
		}
	}
	return (pos);
}

<<<<<<< HEAD
=======
/*
**	add function ptr like that "void (*f)()"
*/

>>>>>>> e7188ec344740364d31604d8c921d619072946ef
static int			is_whitespaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\0' || c == '\t')
		return (1);
	return (0);
}

void				ctrl_right(t_bash *data)
{
	t_term			*curr;
	int				len;

	if (data->iterator < (len = ft_strlen(LINE)))
	{
		while (data->iterator < len && is_whitespaces(LINE[data->iterator]))
			arrow_right(data);
		while (data->iterator < len && !is_whitespaces(LINE[data->iterator]))
			arrow_right(data);
	}
}

void				ctrl_left(t_bash *data)
{
	t_term			*curr;
	int				len;

	if (data->iterator)
	{
		while (data->iterator && is_whitespaces(LINE[data->iterator]))
			arrow_left(data);
		while (data->iterator && !is_whitespaces(LINE[data->iterator]))
			arrow_left(data);
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
	else if (ft_strnequ(buff, "\033[1;2D", 6))
		select_back(data);
	else if (ft_strnequ(buff, "\033[1;2C", 6))
		select_next(data);
	else if (ft_strnequ(buff, "\017", 1))
		select_copy(data);
	else if (ft_strnequ(buff, "\002", 1))
		select_paste(data);
}
