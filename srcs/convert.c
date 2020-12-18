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

int		lendelim(char *str, char delim, int start)
{
	int	i;

	i = (str[start] == delim) ? 1 : 0;
	while (str && str[i + start] && str[i + start] != delim)
		i++;
	return (i);
}

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char		*merge_string_from_array(char **src, int size, int start)
{
	char	*new;
	int		count;
	int		i;
	int		j;
	int		p;

	i = -1;
	j = -1;
	count = -1;
	while (++i != size)
		count += ft_strlen(src[start + i]);
	if (!(new = malloc(sizeof(char) * (count + i + 1))))
		return (NULL);
	i = 0;
	while (i != size)
	{
		p = -1;
		while (src[start + i][++p])
			new[++j] = src[start + i][p];
		i++;
		if (i != size)
			new[++j] = ' ';
	}
	new[++j] = '\0';
	return (new);
}
