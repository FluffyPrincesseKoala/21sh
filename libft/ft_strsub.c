/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:38:08 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 22:04:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	new = ft_strnew(len);
	if (!s || !len)
		return (NULL);
	while (s[j] && j != start)
		j += 1;
	if (j == start)
	{
		while (i != len && s[j])
		{
			new[i] = (char)s[j];
			j += 1;
			i += 1;
		}
		new[i] = 0;
		return (new);
	}
	return (NULL);
}

char	*ft_strsub_free(char **s, unsigned int start, unsigned int len)
{
	char			*ret;
	unsigned int	i;

	if (!len)
	{
		ft_strdel(s);
		return (NULL);
	}
	ret = ft_strnew(len);
	if (!s || !*s || !ret)
		return (NULL);
	i = start;
	while (i - start < len)
	{
		ret[i - start] = (*s)[i];
		i += 1;
	}
	ret[i - start] = '\0';
	ft_strdel(s);
	return (ret);
}
