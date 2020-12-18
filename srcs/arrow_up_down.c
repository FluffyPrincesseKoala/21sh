/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:20:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/02 12:59:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			len_between_last_delim(char *str, char delim, int start)
{
	int				i;

	i = (str[start] == delim) ? 1 : 0;
	while (start - i > 0 && str[start - i] != delim)
		i++;
	return (i);
}

int					get_curent_line(char *str, int pos, int max, int prompt)
{
	int				i;
	int				y;
	int				len_max;

	i = 0;
	y = 0;
	while (i != pos)
	{
		if (str[i] == '\n')
		{
			if (y)
			{
				y += (lendelim(str, '\n', i) - i) / max;
			}
			y++;
		}
		i++;
	}
	return (y);
}

void			clear_term(char *str)
{
	int				i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
		{
			ft_putchar('\n');
		}
		else
			ft_putchar(' ');
		i++;
	}
}

void				arrow_up(t_bash *data)
{
	int		count;
	char	*old;

	old = NULL;
	if (VECT_UP)
	{
		data->history_stack++;
		old = ft_strdup(LINE);
		key_start(data);
		SAVE_C;
		clear_term(old);
		RESET_C;
		if (!VECT_DOWN)
		{
			count = data->history_stack;
			while (count-- && VECT_UP)
				VECT = VECT_UP;
		}
		else
			VECT = VECT_UP;
		count = print_rest(LINE, data->iterator, NULL);
		fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, ft_strlen(LINE), get_win_max_col(), data->prompt_len);
		data->x = ft_strlen(data->cursor->line);
		data->y = get_y_cursor(data->cursor);
		data->iterator = ft_strlen(LINE);
		ft_strdel(&old);
	}
}

void				arrow_down(t_bash *data)
{
	int				len;
	int				count;
	char			*old;

	if (VECT_DOWN || data->history_stack)
	{
		data->history_stack--;
		old = ft_strdup(LINE);
		key_start(data);
		SAVE_C;
		clear_term(old);
		RESET_C;
		if (!VECT_DOWN)
		{
			count = data->history_stack;
			while (count-- > 0 && VECT_UP)
				VECT = VECT_UP;
		}
		else
			VECT = VECT_DOWN;
		count = print_rest(LINE, data->iterator, NULL);
		fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, ft_strlen(LINE), get_win_max_col(), data->prompt_len);
		if (data->cursor)
		{
			data->x = ft_strlen(data->cursor->line);
			data->y = get_y_cursor(data->cursor);
		}
		data->iterator = ft_strlen(LINE);
		ft_strdel(&old);
	}
}