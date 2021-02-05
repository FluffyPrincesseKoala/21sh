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
	if (LINE)
	{
		fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
												get_win_max_col(), data->prompt_len);
		while (data->iterator < ft_strlen(LINE))
			move_right(data);
		clear_struct(&data->cursor);
	}
}

void				key_start(t_bash *data)
{
	int				prompt_len;

	if (data->iterator)
	{
		fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
		data->cursor = find_cursor_node(&data->cursor, data->iterator,
												get_win_max_col(), data->prompt_len);
		while (IDX && (data->x || data->y))
			move_left(data);
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
		old = ft_strdup(LINE);
		ft_strdel(&LINE);
		LINE = ft_strdup(tmp);
		SAVE_C;
		print_rest(NULL, IDX, old);
		RESET_C;
		print_rest(LINE, IDX, NULL);
		RESET_C;
		ft_strdel(&old);
		ft_strdel(&tmp);
	}
}

void				key_suppr(t_bash *data)
{
	char			*tmp;
	char			*old;
	int				expected;

	if (IDX < ft_strlen(LINE))
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
