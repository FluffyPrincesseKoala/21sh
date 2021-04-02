/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_key_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:01:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:07:49 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	init_arrow_functions(t_key **fct)
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
}

/*
**	clean screen: ctrl + L
*/

static void	init_ctrl_key_functions(t_key **fct)
{
	(*fct)[6].f = &ctrl_left;
	(*fct)[6].name = ft_strdup("\033[1;5D");
	(*fct)[6].len = 6;
	(*fct)[7].f = &ctrl_right;
	(*fct)[7].name = ft_strdup("\033[1;5C");
	(*fct)[7].len = 6;
	(*fct)[8].f = &ctrl_down;
	(*fct)[8].name = ft_strdup("\033[1;5B");
	(*fct)[8].len = 6;
	(*fct)[9].f = &ctrl_up;
	(*fct)[9].name = ft_strdup("\033[1;5A");
	(*fct)[9].len = 6;
	(*fct)[16].f = &clean_screen;
	(*fct)[16].name = ft_strdup("\f");
	(*fct)[16].len = 1;
	(*fct)[17].f = &return_exit;
	(*fct)[17].name = ft_strdup("\004");
	(*fct)[17].len = 1;
}

/*
** select_copy: ctrl + shift + left
** select_paste: ctrl + shift + right
*/

static void	init_selection_functions(t_key **fct)
{
	(*fct)[12].f = &select_back;
	(*fct)[12].name = ft_strdup("\033[1;2D");
	(*fct)[12].len = 6;
	(*fct)[13].f = &select_next;
	(*fct)[13].name = ft_strdup("\033[1;2C");
	(*fct)[13].len = 6;
	(*fct)[14].f = &select_copy;
	(*fct)[14].name = ft_strdup("\002");
	(*fct)[14].len = 1;
	(*fct)[15].f = &select_paste;
	(*fct)[15].name = ft_strdup("\016");
	(*fct)[15].len = 1;
}

static void	init_simple_key_functions(t_key **fct)
{
	(*fct)[4].f = &key_suppr;
	(*fct)[4].name = ft_strdup("\033[3~");
	(*fct)[4].len = 4;
	(*fct)[5].f = &key_back;
	(*fct)[5].name = ft_strdup("\177");
	(*fct)[5].len = 1;
	(*fct)[10].f = &key_start;
	(*fct)[10].name = ft_strdup("\033[H");
	(*fct)[10].len = 3;
	(*fct)[11].f = &key_last;
	(*fct)[11].name = ft_strdup("\033[F");
	(*fct)[11].len = 3;
}

void	init_key_functions(t_key **fct)
{
	*fct = ft_memalloc(sizeof(t_key) * MAX_KEY);
	if (!(*fct))
		return ;
	init_arrow_functions(fct);
	init_ctrl_key_functions(fct);
	init_selection_functions(fct);
	init_simple_key_functions(fct);
}
