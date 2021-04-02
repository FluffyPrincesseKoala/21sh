/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:34:58 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 22:09:55 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*pdestre;

	pdestre = dest;
	while (*src != '\0' && n > 0)
	{
		*pdestre++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*pdestre++ = '\0';
		n--;
	}
	return (dest);
}
