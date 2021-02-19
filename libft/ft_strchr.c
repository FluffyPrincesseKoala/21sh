/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:32:07 by cylemair          #+#    #+#             */
/*   Updated: 2018/12/19 16:32:07 by cylemair         ###   ########.fr       */
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

size_t		ft_strichr(const char *s, int c)
{
	size_t		i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i += 1;
	return (i);
}

size_t		ft_smallest_strichr(const char *s, int c1, int c2)
{
	size_t len_c1;
	size_t len_c2;

	len_c1 = ft_strichr(s, c1);
	len_c2 = ft_strichr(s, c2);
	if (len_c1 <= len_c2)
		return (len_c1);
	else
		return (len_c2);
}