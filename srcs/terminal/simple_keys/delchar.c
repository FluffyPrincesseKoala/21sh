/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:23:38 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:00:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

char	*delchar(char *ref, int pos)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(ref);
	if (ref && len > 0 && pos >= 0)
	{
		new = malloc(sizeof(char) * len);
		if (!new)
			return (NULL);
		i = 0;
		len = 0;
		while (ref[len])
		{
			if (len != pos)
			{
				new[i] = ref[len];
				i++;
			}
			len++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
