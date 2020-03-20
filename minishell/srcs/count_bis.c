/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:50:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 20:01:55 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lendelim(char *str, char delim, int start)
{
	int	i;

	i = start;
	while (str && str[i] && str[i] != delim)
		i++;
	return (i);
}

int		array_cmp(char **a, char **b)
{
	return (array_len(a) != array_len(b));
}
