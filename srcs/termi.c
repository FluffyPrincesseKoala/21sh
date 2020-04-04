/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:25:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/02 19:08:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			print_rest_del(char *str, int pos, char *old)
{
	int		i;

	if (pos < ft_strlen(old) )
	{
		LEFT;
	}
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

int		goto_iterator(t_bash data, int pos)
{
	int		len;

	if (pos < ft_strlen(data.vector->line))
	{
		len = ft_strlen(data.vector->line);
		while (len > pos)
		{
			LEFT;
			len--;
		}
	}
	return (pos);
}

char		*delchar(char *ref, int pos)
{
	char	*new;
	int		len;
	int		i;

	if (ref && (len = ft_strlen(ref)) > 0)
	{
		if (!(new = malloc(sizeof(char) * len)))
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

/*
**	add function ptr like that "void (*f)()"
*/

void		arrow_key(t_bash *data, char *buff)
{
	int		len;
	char	*tmp;

	if (ft_strnequ(buff, "\033[A", 3))
	{
		if ((*data).vector->up)
		{
			if ((*data).iterator)
			{
				(*data).iterator = 0;
				(*data).iterator = goto_iterator(*data, (*data).iterator);
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
				(*data).iterator = goto_iterator(*data, (*data).iterator);
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
		if ((*data).iterator < ft_strlen((*data).vector->line))
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
	else if (ft_strnequ(buff, "\033[3~", 4))
	{
		//suppr \033[3~
		len = ft_strlen((*data).vector->line);
		if ((*data).iterator < len && (tmp = delchar((*data).vector->line, (*data).iterator)))
		{
			print_rest(tmp, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
			(*data).vector->line = tmp;
			(*data).iterator = goto_iterator(*data, (*data).iterator);
		}
		else if (len == 1 && (*data).iterator == 0)
		{
			print_rest(NULL, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
		}
	}
	else if (buff[0] == 127)
	{
		//\177[D
		len = ft_strlen((*data).vector->line);
		if (len && (tmp = delchar((*data).vector->line, --(*data).iterator)))
		{
			print_rest_del(tmp, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
			(*data).vector->line = tmp;
			(*data).iterator = goto_iterator(*data, (*data).iterator);
		}
		else if (len == 1)
		{
			print_rest_del(NULL, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
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
