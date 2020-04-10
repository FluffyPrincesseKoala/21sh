/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:25:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/10 21:27:17 by cylemair         ###   ########.fr       */
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
	if (old && pos < ft_strlen(old))
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
	struct winsize w;
	int		len;
	int		max;
	int		y;
	int		x;

	if (pos < ft_strlen(data.vector->line))
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		max = w.ws_col;
		len = ft_strlen(data.vector->line);
		while (len > pos)
		{
			if (len + data.prompt_len >= max)
			{
				y = (len + data.prompt_len) / max;
				x = (len + data.prompt_len) % max;
				if (!x && y)
				{
					UP;
					len--;
					while (x != max)
					{
						RIGHT;
						x++;
					}
				}
				else
				{
					len--;
					LEFT;
				}
			}
			else
			{
				LEFT;
				len--;	
			}
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
	int		max;
	int		prompt;
	int		y;
	int		x;
	char	*tmp;
	struct winsize w;

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
			(*data).iterator = print_rest((*data).vector->line, (*data).iterator,
							((*data).vector->down) ? (*data).vector->down->line : NULL);
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
		//if (((*data).iterator + (*data).prompt_len) < (tgetnum("co")))
		if ((*data).iterator < ft_strlen((*data).vector->line))
		{
    		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			max = w.ws_col;
			prompt = (*data).prompt_len;
			if (prompt + ft_strlen((*data).vector->line) >= max)
			{
				y = ((*data).iterator + (*data).prompt_len) / max;
				x = ((*data).iterator + (*data).prompt_len) % max;
				if (x == max - 1)
				{
					CDOWN;
					(*data).iterator++;
					return ;
				}
			}
			(*data).iterator++;
			RIGHT;
		}
	}
	else if (ft_strnequ(buff, "\033[D", 3))
	{
		if ((*data).iterator)
		{
    		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			max = w.ws_col;
			prompt = (*data).prompt_len;
			if ((*data).iterator + (*data).prompt_len >= max)
			{
				y = ((*data).iterator + (*data).prompt_len) / max;
				x = ((*data).iterator + (*data).prompt_len) % max;
				if (!x && y)
				{
					UP;
					(*data).iterator--;
					while (x != max)
					{
						RIGHT;
						x++;
					}
					return ;
				}
			}
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
			if ((*data).vector->down)
				pull_line(&(*data).vector);
			print_rest_del(tmp, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
			(*data).vector->line = tmp;
			(*data).iterator = goto_iterator(*data, (*data).iterator);
		}
		else if (len == 1)
		{
			if ((*data).vector->down)
				pull_line(&(*data).vector);
			print_rest_del(NULL, (*data).iterator, (*data).vector->line);
			ft_strdel(&(*data).vector->line);
		}
	}
	else if (ft_strnequ(buff, "\033[1;5D", 6) && (*data).iterator)
	{
		//ctrl + left
		len = (*data).iterator;
		while (len)
		{
			if (len)
			{
				len--;
				(*data).iterator--;
				LEFT;
			}
			if ((*data).vector->line[(*data).iterator] == ' ')
			{
				(*data).iterator = len;
				len = 0;
			}
		}
	}
	else if (ft_strnequ(buff, "\033[1;5C", 6))
	{
		//ctrl + right
		len = (*data).iterator;
		while (len < ft_strlen((*data).vector->line))
		{
			if (len < ft_strlen((*data).vector->line))
			{
				len++;
				(*data).iterator++;
				RIGHT;
			}
			if ((*data).vector->line[(*data).iterator] == ' ')
			{
				(*data).iterator = len;
				len = ft_strlen((*data).vector->line);
			}
		}
	}
	else if (ft_strnequ(buff, "\033[H", 3))
	{
		while ((*data).iterator)
		{
			(*data).iterator--;
			LEFT;
		}
	}
	else if (ft_strnequ(buff, "\033[F", 3))
	{
		while ((*data).iterator < ft_strlen((*data).vector->line))
		{
			(*data).iterator++;
			RIGHT;
		}
	}
}
