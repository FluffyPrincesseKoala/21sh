/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:11:39 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 13:01:42 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	print_nb_history(t_vect *lst, int nb)
{
	t_vect	*count;
	int		stack;

	stack = 0;
	while (lst->down)
		lst = lst->down;
	while (--nb && lst->up)
		lst = lst->up;
	count = lst;
	while (count->up && ++stack)
		count = count->up;
	while (lst)
	{
		ft_putnbr(++stack);
		ft_putstr("\t| ");
		ft_putendl(lst->line);
		lst = lst->down;
	}
}

void		print_history(t_bash *data)
{
	t_vect	*vect;
	int		i;

	i = 0;
	if ((vect = data->vector))
	{
		while (vect->up)
			vect = vect->up;
		while (vect)
		{
			ft_putnbr(++i);
			ft_putstr("\t| ");
			ft_putendl(vect->line);
			vect = vect->down;
		}
	}
}

void		history(t_bash *data, t_vect *cmd)
{
	int		i;
	t_vect	*lst;

	if (cmd->args && cmd->args->next
		&& ft_str_is_digits(cmd->args->next->content))
	{
		lst = cmd;
		if ((i = ft_atoi(cmd->args->next->content)))
			print_nb_history(lst, i);
	}
	else
		print_history(data);
}
