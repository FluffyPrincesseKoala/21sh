/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 17:18:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/01 21:04:00 by cylemair         ###   ########.fr       */
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
	int				prompt_len;

	if (data->iterator)
	{
		fit_line_in_terminal(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_node_by_iterator(&data->cursor, data->iterator,
												get_win_max_col(), data->prompt_len);
		while (IDX)
		{
			move_left(data);
			// if (data->cursor->x)
			// {
			// 	LEFT;
			// 	data->cursor->x--;
			// }
			// else if (data->cursor->y)
			// {
			// 	UP;
			// 	if (!--data->cursor->y)
			// 	{
			//  		prompt_len = data->prompt_len;
			//  		while (prompt_len--)
		 	// 			RIGHT;
			// 	}
			// }
		}
		clear_struct(&data->cursor);
	}
}

void				key_back(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (IDX && ft_strlen(LINE))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		tmp = delchar(LINE, IDX - 1);
		expected = IDX - 1;
		arrow_left(data);
		old = LINE;
		LINE = tmp;
		SAVE_C;
		print_rest(NULL, IDX, old);
		RESET_C;
		print_rest(LINE, IDX, NULL);
		RESET_C;
	}
}

void				key_suppr(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (ft_strlen(LINE))
	{
		if (data->vector->down)
			pull_line(&data->vector);
		tmp = delchar(LINE, IDX);
		expected = IDX;
		old = LINE;
		LINE = tmp;
		SAVE_C;
		print_rest(NULL, IDX, old);
		RESET_C;
		print_rest(LINE, IDX, NULL);
		RESET_C;
	}
}
