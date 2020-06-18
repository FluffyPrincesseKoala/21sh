/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 17:18:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char			*delchar(char *ref, int pos)
{
	char			*new;
	int				len;
	int				i;

	if (ref && (len = ft_strlen(ref)) > 0 && pos >= 0)
	{
		if (!(new = malloc(sizeof(char) * len)))
			return (NULL);
		i = 0;
		len = 0;
		while (ref[len])
		{
			if (len != pos)
			{
				new[i] = ref[len];
				i++;
			}
			len++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

void				key_last(t_bash *data)
{
	struct winsize	w;
	int				prompt;
	int				y;
	int				x;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	prompt = data->prompt_len;
	while (data->iterator < ft_strlen(data->vector->line))
	{
		init_xy(data, &x, &y, w.ws_col);
		if (x == w.ws_col - 1 || LINE[data->iterator] == '\n')
			CDOWN;
		else
			RIGHT;
		data->iterator++;		
	}
}

void				key_start(t_bash *data)
{
	struct winsize	w;
	int				prompt;
	int				y;
	int				x;
	int				cur;
	int				last;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	prompt = data->prompt_len;
	cur = 0;
	last = 0;
	while (data->iterator && data->iterator != data->start_expend)
	{
		init_xy(data, &x, &y, w.ws_col);
		if (LINE[data->iterator - 1] == '\n')
		{
			UP;
			while (last && --last)
				LEFT;
			last = len_between_last_delim(LINE, '\n', data->iterator - 1);
			if (data->start_expend == last)
				RIGHT;
			cur = (y == 1) ? prompt + last + 1 : last;
			while (--cur)
				RIGHT;
		}
		else if (!x && y)
		{
			UP;
			while (x++ != w.ws_col)
				RIGHT;
			int lapin = w.ws_col - ((y == 1) ? prompt : 0) + lendelim(LINE, '\n', 0);
			while (LINE[data->iterator - 1] == '\n'
			&& x-- > lapin)
				LEFT;
		}
		else
			LEFT;
		data->iterator--;
	}
}

void				key_back(t_bash *data)
{
	char			*tmp;
	int				len;

	len = 0;
	if (data->iterator && (len = ft_strlen(data->vector->line))
		&& (tmp = delchar(data->vector->line, data->iterator - 1)))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		arrow_left(data);
		SAVE_C;
		len = data->iterator;
		print_rest(tmp, data->iterator, data->vector->line);
		RESET_C;
		data->iterator = len;
		ft_strdel(&data->vector->line);
		data->vector->line = tmp;
	}
	else if (data->iterator == len && len == 1)
	{
		if (data->vector->down)
			pull_line(&data->vector);
		print_rest(NULL, data->iterator, data->vector->line);
		ft_strdel(&data->vector->line);
	}
}

void				key_suppr(t_bash *data)
{
	char			*tmp;
	int				len;

	len = ft_strlen(data->vector->line);
	if (len == 1 && data->iterator == 0)
	{
		SAVE_C;
		print_rest(NULL, data->iterator, data->vector->line);
		ft_strdel(&data->vector->line);
		RESET_C;
	}
	else if (data->iterator < len && (tmp = delchar(data->vector->line, data->iterator)))
	{
		SAVE_C;
		print_rest(tmp, data->iterator, data->vector->line);
		ft_strdel(&data->vector->line);
		data->vector->line = tmp;
		RESET_C;
	}
}
