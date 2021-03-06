/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iseven.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:27:59 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:36:11 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iseven(int nb)
{
	float	check;

	check = (float)nb / 2;
	check -= (float)nb / 2;
	return (check == 0);
}
