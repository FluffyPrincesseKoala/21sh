/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:33:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 22:14:40 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[i] = (char)s1[i];
		i += 1;
	}
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin_free(char **s1, char **s2, int s_to_free)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = NULL;
	ret = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(*s2) + 1));
	if (!ret)
		return (NULL);
	while (*s1 && (*s1)[i])
	{
		ret[i] = (char)(*s1)[i];
		i += 1;
	}
	while (*s2 && (*s2)[j])
		ret[i++] = (*s2)[j++];
	ret[i] = '\0';
	if (s_to_free == FREE_S1 || s_to_free == FREE_BOTH)
		ft_strdel(s1);
	if (s_to_free == FREE_S2 || s_to_free == FREE_BOTH)
		ft_strdel(s2);
	return (ret);
}
