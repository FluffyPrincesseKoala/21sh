/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:54:50 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/04 19:55:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		streplace(char **s1, char **s2)
{
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
}

void		puterror(char *error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
}

void		putab(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
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

char		*replace_delim(char *str, char delim, char new)
{
	char	*ret;
	char	**tmp;
	size_t	len;
	int		i[3];

	i[1] = 0;
	i[0] = 0;
	tmp = ft_strsplit(str, delim);
	len = array_total_len(tmp) + array_len(tmp);
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (tmp[i[0]])
	{
		i[2] = 0;
		ret = (tmp[i[0]][i[2]]) ? stracat(tmp, ret, i) : ret;
		i[0]++;
		if (tmp[i[0]])
		{
			ret[i[1]] = new;
			i[1]++;
		}
	}
	ret[i[1]] = '\0';
	free_array(tmp);
	return (ret);
}
