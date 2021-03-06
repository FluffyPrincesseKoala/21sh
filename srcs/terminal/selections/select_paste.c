/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:41:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 11:55:10 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

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
		if (data->vector->line && ft_strlen(data->vector->line))
		{
			old = ft_strdup(data->vector->line);
			ft_strdel(&data->vector->line);
			data->vector->line = str_add_sub(old, data->copied, data->iterator);
		}
		else
		{
			ft_strdel(&data->vector->line);
			data->vector->line = ft_strdup(data->copied);
		}
		term_put(SAVE);
		print_rest(data->vector->line, data->iterator, old);
		term_put(RESET_C);
		ft_strdel(&old);
	}
}
