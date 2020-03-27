/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:25:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 20:01:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			print_rest(char *str, int pos, char *old)
{
	int		i;

	while (str && str[pos])
	{
		ft_putchar(str[pos]);
		pos++;
	}
	if (old)
	{
		i = pos;
		while (old[i])
		{
			ft_putchar(' ');
			i++;
		}
		while (i != pos)
		{
			LEFT;
			i--;
		}
	}
	return (pos);
}

void		goto_iterator(t_bash data)
{
	int		len;

	if (data.iterator < ft_strlen(data.vector->line))
	{
		len = ft_strlen(data.vector->line);
		while (len > data.iterator)
		{
			LEFT;
			len--;
		}
	}
}

char		*delchar(char *ref, int pos)
{
	char	*new;
	int		len;
	int		i;

	if (pos && (len = ft_strlen(ref)))
	{
		if (!(new = malloc(sizeof(char) * len)))
			return (NULL);
		new[len] = '\0';
		i = len;
		while (len--)
		{
			if (len != pos)
				new[i--] = ref[len];
		}
		return (new);
	}
	return (NULL);
}

void		arrow_key(t_bash *data, char *buff)
{
	if (ft_strnequ(buff, "\033[A", 3))
	{
		if ((*data).vector->up)
		{
			if ((*data).iterator)
			{
				(*data).iterator = 0;
				goto_iterator(*data);
			}
			/*
			** copy actual vector to vect->down
			*/
			(*data).vector = (*data).vector->up;
			(*data).iterator = print_rest((*data).vector->line, (*data).iterator, (*data).vector->down->line);
		}
	}
	else if (ft_strnequ(buff, "\033[B", 3))
	{
		if ((*data).vector->down)
		{
			if ((*data).iterator)
			{
				(*data).iterator = 0;
				goto_iterator(*data);
			}
			/*
			** copy actual vector to vect->down
			*/
			(*data).vector = (*data).vector->down;
			(*data).iterator = print_rest((*data).vector->line, (*data).iterator,
			((*data).vector->up) ? (*data).vector->up->line : NULL);
		}
	}
	else if (ft_strnequ(buff, "\033[C", 3))
	{
		if ((*data).vector->line[(*data).iterator])
		{
			(*data).iterator++;
			RIGHT;
		}
	}
	else if (ft_strnequ(buff, "\033[D", 3))
	{
		if ((*data).iterator)
		{
			(*data).iterator--;
			LEFT;
		}
	}
	else if (ft_strnequ(buff, "\033[H", 4))
	{
		//suppr \033[3~
	}
	else if (buff[0] == 127)
	{
		//\177[D
		char *tmp;
		if ((tmp = delchar((*data).vector->line, (*data).iterator - 1)))
		{
			print_rest(tmp, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
			(*data).vector->line = tmp;
		}
	}
	else if (ft_strnequ(buff, "\033[1;5D", 6) && (*data).iterator)
	{
		//ctrl + left
		while ((*data).iterator && (*data).vector->line[(*data).iterator] != ' ')
		{
			(*data).iterator--;
			LEFT;
		}
	}
	else if (ft_strnequ(buff, "\033[1;5C", 6))
	{
		int len = (*data).iterator;
		//ctrl + right
		while ((*data).iterator < ft_strlen((*data).vector->line)
			&& (*data).vector->line[(*data).iterator] != ' ')
		{
			(*data).iterator++;
			RIGHT;
		}
	}
}
