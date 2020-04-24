/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 17:18:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/24 16:36:10 by cylemair         ###   ########.fr       */
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
		y = (data->iterator + prompt) / w.ws_col;
		x = (data->iterator + prompt) % w.ws_col;
		if (x == w.ws_col - 1)
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

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	prompt = data->prompt_len;
	while (data->iterator)
	{
		y = (data->iterator + prompt) / w.ws_col;
		x = (data->iterator + prompt) % w.ws_col;
		if (!x && y)
		{
			UP;
			while (x++ != w.ws_col)
				RIGHT;
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
