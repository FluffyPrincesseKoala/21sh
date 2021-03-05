/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:39:22 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/04 19:32:40 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	contains_sperator(char *str)
{
	int		i;
	int		j;
	char	*separator;

	i = 0;
	separator = ";\n|";
	while (str && str[i])
	{
		j = 0;
		while (separator[j])
		{
			if (str[i] == separator[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

t_arg		*create_arg(char *content)
{
	t_arg	*new;

	if (new = ft_memalloc(sizeof(t_arg)))
	{
		if (new->content = content)
		{
			new->separator = contains_sperator(content);
			return (new);
		}
		else
		{
			new->content = NULL;
			new->separator = contains_sperator(content);
			return (new);
		}
	}
	ft_strdel(&content);
	return (NULL);
}
