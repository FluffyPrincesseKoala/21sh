/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:58:43 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 11:25:08 by cylemair         ###   ########.fr       */
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
	while (str && str[i])
	{
		if (i == pos)
			new[j++] = c;
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

void		push_entry(t_bash *data, char *entry, char **line, int pos)
{
	char	*tmp;

	tmp = NULL;
	if (data->iterator || *line)
		tmp = addchar(*line, entry[0], pos);
	else
		tmp = ft_strndup(entry, 1);
	ft_strdel(line);
	*line = ft_strdup(tmp);
	ft_strdel(&tmp);
}
