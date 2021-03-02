/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:56:07 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 13:05:02 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	print_args(t_bash *data, t_vect *command)
{
	t_arg	*arg;

	if (command->args)
		arg = command->args->next;
	while (arg)
	{
		ft_putstr(arg->content);
		if (arg->next)
			ft_putchar(' ');
		arg = arg->next;
	}
	ft_putchar('\n');
}
