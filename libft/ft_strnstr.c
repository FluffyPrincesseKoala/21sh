/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:35:11 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 22:08:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i] && i < len && ft_strlen(to_find) <= len - i)
	{
		j = 0;
		while (str[i] == to_find[j] && str[i])
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&str[i - j]);
			i += 1;
			j += 1;
		}
		i = i + 1 - j;
	}
	return (0);
}
