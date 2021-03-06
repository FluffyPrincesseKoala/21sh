/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen_in_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:37:18 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraylen_in_char(char **array)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	return (len);
}
