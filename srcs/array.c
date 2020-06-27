/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/12 17:47:43 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**copy_array(char **array)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	while (array[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int			array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int			array_total_len(char **array)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	return (len);
}

void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		ft_strdel(&array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

void		print_array(char **array)
{
	int i;

	i=0;
	ft_putchar('\n');
	while (array && array[i])
	{
		ft_putstr(array[i]);
		ft_putchar('\n');
		i++;
	}
}
