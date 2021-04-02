/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:30:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/02 18:34:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*buff;

	buff = (char *)s;
	while (n)
	{
		*buff = c;
		if (n)
			buff += 1;
		n -= 1;
	}
	return (s);
}
