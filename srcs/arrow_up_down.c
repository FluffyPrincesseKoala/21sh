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

static void	clear_term(char *str)
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

static int	get_y_cursor(t_term *src)
{
	int				count;

	count = 0;
	while (src->prev)
	{
		src = src->prev;
		count += 1;
	}
	return (count);
}

void		arrow_up(t_bash *data)
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
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, ft_strlen(LINE), get_win_max_col(), data->prompt_len);
		data->x = ft_strlen(data->cursor->line);
		data->y = get_y_cursor(data->cursor);
		data->iterator = ft_strlen(LINE);
		ft_strdel(&old);
	}
}

void		arrow_down(t_bash *data)
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
		set_cursors(data, &data->cursor, LINE, get_win_max_col());
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