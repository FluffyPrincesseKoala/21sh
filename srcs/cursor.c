/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 18:05:26 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/17 16:19:29 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int					count_delim_befor(char *str, int pos, char delim)
{
	int				i;
	int				count;

	i = (str[pos] == delim) ? 1 : 0;
	count = 0;
	while (str && pos && str[pos - i])
	{
		if (str[i - pos] == delim)
			count++;
		i++;
	}
	return (count);
}

t_term				*new_cursor_struct(char *line, int end, int start)
{
	t_term			*cursor;

	if (!(cursor = malloc(sizeof(t_term))))
		return (NULL);
	cursor->line = ft_strdup(line);
	cursor->line_end = end;
	cursor->line_start = start;
	cursor->next = NULL;
	cursor->prev = NULL;
}

fit_line_in_terminal(t_bash *data, t_term *cursor, char *str, int max)
{
	int				i;
	int				j;
	char			new_line[max + 1];

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (j == max || str[i] == '\n')
		{
			new_line[j] = '\0';
			cursor->line = ft_strdup(new_line);
			cursor->line_end = i;
			cursor->line_start = i - j;
			ft_bzero(new_line, max);
			j = 0;
		}
		else
		{
			new_line[j] = str[i];
			j++;
		}
		i++;
	}
}

void				init_cursor(t_bash *data)
{
	t_term			*new;
	struct winsize	w;

	if (!(new = malloc(sizeof(t_term))))
		return ;
	new->y = 0;
	new->x = 0;
	new->line_start = 0;
	new->line_end = 0;
	fit_line_in_terminal(LINE);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
}