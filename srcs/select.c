
#include "21sh.h"

void	apply_back_select(t_bash *data)
{
	int	i;
	int	j;

	i = 0;
	j = data->iterator;
	SAVE_C;
	ft_putstr(BACK_BLUE);
	while (LINE && LINE[j])
	{
		if (i == data->end_select)
			ft_putstr(RESET);
		ft_putchar(LINE[j]);
		i++;
		j++;
	}
	if (i == data->end_select)
		ft_putstr(RESET);
	RESET_C;
}

void	apply_select(t_bash *data)
{
	int	i;
	int	j;

	i = 0;
	j = data->iterator;
	SAVE_C;
	ft_putstr(BACK_BLUE);
	while (LINE && LINE[j])
	{
		ft_putchar(LINE[j]);
		i++;
		j++;
		if (i == 1)
			ft_putstr(RESET);
	}
	RESET_C;
}

void	select_back(t_bash *data)
{
	if (data->iterator)
	{
		if (data->is_select)
			data->end_select += (data->select_direction == -1) ? 1 : -1;
		else if (!data->is_select)
		{
			data->is_select = 1;
			data->start_select = data->iterator;
			data->end_select = 1;
			data->select_direction = -1;
		}
		if (data->end_select && data->start_select)
		{
			data->is_select = 0;
			data->is_select = 0;
			if (data->select_direction == -1)
			{
				arrow_left(data);
				apply_back_select(data);
			}
			else
			{
				arrow_left(data);
				SAVE_C;
				ft_putchar(LINE[data->iterator]);
				RESET_C;
			}
			data->is_select = 1;
		}
	}
}

void	select_next(t_bash *data)
{
	if (data->iterator != ft_strlen(LINE))
	{
		if (data->is_select)
			data->end_select += (data->select_direction == 1) ? 1 : -1;
		else if (!data->is_select)
		{
			data->is_select = 1;
			data->start_select = data->iterator;
			data->end_select = 1;
			data->select_direction = 1;
		}
		if (data->end_select && data->is_select)
		{
			data->is_select = 0;
			if (data->select_direction == 1)
			{
				apply_select(data);
				arrow_right(data);
			}
			else
			{
				int save = data->iterator;
				SAVE_C;
				arrow_left(data);
				ft_putchar(LINE[data->iterator]);
				RESET_C;
				data->iterator = save;
			}
			data->is_select = 1;
		}
	}
}

static char	*strsub_copy(char *str, int start, int size)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str || !(ret = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (str[start] && i != size)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

void	uncolor(t_bash *data)
{
	int	save;

	save = data->iterator;
	fill_term_struct(data, &data->cursor, LINE, get_win_max_col());
	if (data->cursor)
	{
		data->cursor = find_cursor_node(&data->cursor,	data->iterator,
												get_win_max_col(), data->prompt_len);
		if (data->select_direction == -1)
		{
			SAVE_C;
			print_rest(LINE, save, NULL);
			RESET_C;
		}
		else if (data->select_direction == 1)
		{
			SAVE_C;
			for (int i = 0 ; i != data->end_select ; i++)
				move_left(data);
			print_rest(LINE, data->iterator, NULL);
			RESET_C;
			data->iterator = save;
		}
	}
}

void	unselect(t_bash *data)
{
	data->is_select = 0;
	data->end_select = 0;
	data->start_select = 0;
	data->select_direction = 0;
}

void	select_copy(t_bash *data)
{
	int	start;

	if (data->is_select)
	{
		start = (data->select_direction == -1) ? data->iterator : data->iterator - data->end_select;
		data->copied = strsub_copy(LINE, start, data->end_select);
		info(data->copied);
		uncolor(data);
		unselect(data);
		clear_struct(&data->cursor);
		info(data->copied);
	}
}

void	select_paste(t_bash *data)
{
	char	*old;

	if (data->copied)
	{
		if (LINE)
		{
			old = ft_strdup(LINE);
			LINE = str_add_sub(LINE, data->copied, IDX);
		}
		else
			LINE = data->copied;
		SAVE_C;
		print_rest(LINE, IDX, old);
		RESET_C;
	}
}
