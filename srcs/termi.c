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

static void		init_arrow_fct_ptr_A(t_key **fct)
{
	(*fct)[0].f = &arrow_up;
	(*fct)[0].name = ft_strdup("\033[A");
	(*fct)[0].len = 3;
	(*fct)[1].f = &arrow_down;
	(*fct)[1].name = ft_strdup("\033[B");
	(*fct)[1].len = 3;
	(*fct)[2].f = &arrow_right;
	(*fct)[2].name = ft_strdup("\033[C");
	(*fct)[2].len = 3;
	(*fct)[3].f = &arrow_left;
	(*fct)[3].name = ft_strdup("\033[D");
	(*fct)[3].len = 3;
	(*fct)[4].f = &key_suppr;
	(*fct)[4].name = ft_strdup("\033[3~");
	(*fct)[4].len = 4;
	(*fct)[5].f = &key_back;
	(*fct)[5].name = ft_strdup("\177");
	(*fct)[5].len = 1;
	(*fct)[6].f = &ctrl_left;
	(*fct)[6].name = ft_strdup("\033[1;5D");
	(*fct)[6].len = 6;
	(*fct)[7].f = &ctrl_right;
	(*fct)[7].name = ft_strdup("\033[1;5C");
	(*fct)[7].len = 6;
}

static void		init_arrow_fct_ptr_B(t_key **fct)
{
	(*fct)[8].f = &ctrl_down;
	(*fct)[8].name = ft_strdup("\033[1;5B");
	(*fct)[8].len = 6;
	(*fct)[9].f = &ctrl_up;
	(*fct)[9].name = ft_strdup("\033[1;5A");
	(*fct)[9].len = 6;
	(*fct)[10].f = &key_start;
	(*fct)[10].name = ft_strdup("\033[H");
	(*fct)[10].len = 3;
	(*fct)[11].f = &key_last;
	(*fct)[11].name = ft_strdup("\033[F");
	(*fct)[11].len = 3;
	(*fct)[12].f = &select_back;
	(*fct)[12].name = ft_strdup("\033[1;2D");
	(*fct)[12].len = 6;
	(*fct)[13].f = &select_next;
	(*fct)[13].name = ft_strdup("\033[1;2C");
	(*fct)[13].len = 6;
	(*fct)[14].f = &select_copy;
	(*fct)[14].name = ft_strdup("\033[1;6D"); //ctrl + shit + left
	(*fct)[14].len = 6;
	(*fct)[15].f = &select_paste;
	(*fct)[15].name = ft_strdup("\033[1;6C"); //ctrl + shit + right
	(*fct)[15].len = 6;
}

static void		init_arrow_fct_ptr(t_key **fct)
{
	if (!(*fct = ft_memalloc(sizeof(t_key) * MAX_KEY)))
		return ;
	init_arrow_fct_ptr_A(fct);
	init_arrow_fct_ptr_B(fct);
}

void		arrow_key(t_bash *data, char *buff)
{
	static t_key	*fct;
	int		i;
	int		exit;

	i = 0;
	exit = 0;
	if (!fct)
		init_arrow_fct_ptr(&fct);
	while (i != MAX_KEY && !exit)
	{
		if (ft_strnequ(buff, fct[i].name, fct[i].len))
		{
			fct[i].f(data);
			exit++;
		}
		i++;
	}
}
