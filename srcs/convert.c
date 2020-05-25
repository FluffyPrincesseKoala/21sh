/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:37:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/05/02 19:28:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_lst		*pop_lst_from_array(char **src, int size, int start)
{
	t_lst	*new;
	int		i;

	i = 0;
	new = NULL;
	while (i != size)
	{
		if (new)
			lstadd(&new, lstnew(src[start + i]));
		else
			new = lstnew(src[start + i]);
		i++;
	}
	return (new);
}

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
