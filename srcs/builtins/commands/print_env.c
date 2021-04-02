/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:51:15 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 19:19:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	print_env(t_bash *data, t_vect *cmd)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		ft_putnbr(i);
		ft_putchar('|');
		ft_putendl(data->env[i]);
		i++;
	}
}
