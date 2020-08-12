/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:31:27 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/24 18:06:16 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*addchar(char *str, char c, int pos)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 2))))
		return (NULL);
	while (str[i])
	{
		if (i == pos)
		{
			new[j] = c;
			j++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	if (i == pos)
	{
		new[j] = c;
		j++;
	}
	new[j] = '\0';
	return (new);
}

int pstr(char const *str)
{
	if (str)
		return(write(1, str, ft_strlen((char *)str)));
	return (0);
}

int pchar(int c)
{
	return(write(1, &c, 1));
}

size_t		count_delim(char *str, int delim)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == delim)
			count++;
		i++;
	}
	return (count);
}

static char	*stracat(char **tmp, char *ret, int *i)
{
	while (tmp[i[0]][i[2]])
	{
		ret[i[1]] = tmp[i[0]][i[2]];
		i[1]++;
		i[2]++;
	}
	return (ret);
}
