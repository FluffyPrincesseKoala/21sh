/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:29:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/02 18:42:45 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char *)s1++ = *(unsigned char *)s2;
		if (*(unsigned char *)s2++ == (unsigned char)c)
		{
			return (s1);
		}
	}
	return (NULL);
}
