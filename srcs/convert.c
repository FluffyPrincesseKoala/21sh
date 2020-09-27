/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:37:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/03 18:32:57 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*merge_string_from_array(char **src, int size, int start)
{
	char	*new;
	int		count;
	int		i;
	int		j;
	int		p;

	i = -1;
	j = 0;
	count = -1;
	new = NULL;
	while (++i != size)
		count += ft_strlen(src[start + i]);
	if (!(new = malloc(sizeof(char) * (count + i + 1))))
		return (NULL);
	i = 0;
	while (i != size)
	{
		p = -1;
		while (src[start + i][++p])
		{
			new[j] = src[start + i][p];
			j++;
		}
		i++;
		if (i != size)
		{
			new[j] = ' ';
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}
