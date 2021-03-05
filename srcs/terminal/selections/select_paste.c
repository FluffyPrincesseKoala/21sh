/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:41:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 16:52:54 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char	*ncat(char *new, char *sub, int *j)
{
	int		k;

	k = 0;
	while (sub[k])
	{
		new[++*j] = sub[k];
		k++;
	}
	return (new);
}

static char	*str_add_sub(char *str, char *sub, int pos)
{
	char	*new;
	int		ok;
	int		i;
	int		j;

	i = 0;
	j = -1;
	ok = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(sub) + 1))))
		return (NULL);
	while (str && str[i])
	{
		if (i != pos || ok)
			new[++j] = str[i++];
		else
		{
			new = ncat(new, sub, &j);
			ok = 1;
		}
	}
	if (i == pos && !ok)
		new = ncat(new, sub, &j);
	new[++j] = '\0';
	return (new);
}

void		select_paste(t_bash *data)
{
	char	*old;

	old = NULL;
	if (data->copied)
	{
		if (LINE && ft_strlen(LINE))
		{
			old = ft_strdup(LINE);
			ft_strdel(&LINE);
			LINE = str_add_sub(old, data->copied, IDX);
		}
		else
		{
			ft_strdel(&LINE);
			LINE = ft_strdup(data->copied);
		}
		SAVE_C;
		print_rest(LINE, IDX, old);
		RESET_C;
		ft_strdel(&old);
	}
}
