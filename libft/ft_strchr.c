/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:32:07 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:31:12 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i += 1;
	if (s && s[i] == c)
		return ((char*)s + i);
	return (NULL);
}

size_t		ft_strichr(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i += 1;
	return (i);
}

size_t		ft_smallest_strichr(const char *s, char *delims)
{
	size_t smallest_len;
	size_t current_len;
	size_t i;

	i = 0;
	smallest_len = ft_strlen(s);
	while (delims && delims[i])
	{
		current_len = ft_strichr(s, delims[i]);
		if (current_len < smallest_len)
			smallest_len = current_len;
		i++;
	}
	return (smallest_len);
}
