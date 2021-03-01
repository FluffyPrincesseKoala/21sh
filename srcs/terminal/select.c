
#include "21sh.h"

static void		reset_back(t_bash *data)
{
	data->end_select -= 1;
	data->is_select = 0;
	arrow_left(data);
	SAVE_C;
	ft_putchar(LINE[data->end_select]);
	RESET_C;
	data->is_select = SRIGHT;
	if (data->end_select == data->start_select)
		unselect(data);
}

static void		add_back(t_bash *data)
{
	data->is_select = 0;
	arrow_left(data);
	SAVE_C;
	ft_putstr(BACK_BLUE);
	ft_putchar(LINE[data->start_select]);
	ft_putstr(RESET);
	RESET_C;
	data->is_select = SLEFT;
}

void	select_back(t_bash *data)
{
	if (data->iterator)
	{
		if (data->is_select)
		{
			if (data->is_select == SLEFT)
				data->start_select -= 1;
			else
			{
				reset_back(data);
				return;
			}			
		}
		else
		{
			data->end_select = data->iterator;
			data->start_select = data->iterator - 1;
		}
		if (data->start_select < data->end_select)
			add_back(data);
	}
}

static void		add_next(t_bash *data)
{
	data->is_select = 0;
	SAVE_C;
	ft_putstr(BACK_BLUE);
	ft_putchar(LINE[data->end_select - 1]);
	ft_putstr(RESET);
	RESET_C;
	arrow_right(data);
	data->is_select = SRIGHT;
}

static void		reset_next(t_bash *data)
{
	SAVE_C;
	ft_putchar(LINE[data->start_select]);
	RESET_C;
	data->start_select += 1;
	data->is_select = 0;
	arrow_right(data);
	data->is_select = SLEFT;
	if (data->end_select == data->start_select)
		unselect(data);;
}

void	select_next(t_bash *data)
{
	if (data->iterator < ft_strlen(LINE))
	{
		if (data->is_select)
		{
			if (data->is_select == SRIGHT)
				data->end_select += 1;
			else
			{
				reset_next(data);
				return ;
			}
		}
		else
		{
			data->end_select = data->iterator + 1;
			data->start_select = data->iterator;
		}
		if (data->start_select < data->end_select)
			add_next(data);
	}
}

static char	*strsub_copy(char *str, int start, int size)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str || !(ret = malloc(sizeof(char) * (size - start + 1))))
		return (NULL);
	while (str[start] && start != size)
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
	int	idx;
	int	count;
	int	x;
	int	y;

	idx = data->iterator;
	x = data->x;
	y = data->y;
	while (data->iterator){
		arrow_left(data);
	}
	SAVE_C;
	print_rest(LINE, data->iterator, LINE),
	RESET_C;
	while (data->iterator != idx) {
		arrow_right(data);
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
	if (data->is_select)
	{
		if (data->copied)
			ft_strdel(&data->copied);
		data->copied = strsub_copy(LINE, data->start_select, data->end_select);
		uncolor(data);
		unselect(data);
		//clear_struct(&data->cursor);
	}
}

void	select_paste(t_bash *data)
{
	char	*old;

	old = NULL;
	if (data->copied)
	{
		if (LINE && ft_strlen(LINE))
		{
			old = ft_strdup(LINE);
			ft_strdel(&LINE);
			LINE = str_add_sub(old, data->copied, IDX);
		}
		else
		{
			ft_strdel(&LINE);
			LINE = ft_strdup(data->copied);
		}
		SAVE_C;
		print_rest(LINE, IDX, old);
		RESET_C;
		ft_strdel(&old);
	}
}
