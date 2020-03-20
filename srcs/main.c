/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:43:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/20 18:11:12 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>

int pstr(char const *str)
{
	if (str)
		return(write(1, str, ft_strlen((char *)str)));
}

int init_term()
{
	int ret;
	char *term_type = getenv("TERM");

	if (term_type == NULL)
	{
		printf("TERM must be set (see 'env').\n");
		return -1;
	}

	ret = tgetent(NULL, term_type);

	if (ret == -1)
	{
		printf("Could not access to the termcap database..\n");
		return -1;
	}
	else if (ret == 0)
	{
		printf("Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
		return -1;
	}
	return 0;
}

int				conf_term()
{
	struct termios		term;

	if (!init_term())
	{
		if (tcgetattr(0, &term) == -1)
			return (-1);
		term.c_lflag &= ~(ICANON|ECHO);
		if (tcsetattr(0, 0, &term) == -1)
			return (-1);
		tputs(tgetstr("os", NULL), 1, ft_putchar);
	}
	else
		return (-1);
	return (0);
}

void		hello()
{
	int		column_count = tgetnum("co");
	int		i = 0;
	ft_putstr(CYAN);
	ft_putstr("*");
	while (i < (column_count - 2))
	{
		ft_putchar('*');
		i++;
	}
	ft_putstr("*\n");
	ft_putstr("*");
	while (i-- > ((column_count + 5) / 2))
		ft_putchar(' ');
	ft_putstr("21SH");
	while (i++ < (column_count))
		ft_putchar(' ');
	ft_putstr("*\n");
	ft_putstr("*");
	while (i-- > 3)
		ft_putchar('*');
	ft_putstr("*\n");
	ft_putstr(RESET);
}

int			prompt()
{
	char	*tmp = getenv("USER");
	int		len;

	len = 0;
	len += pstr(BLUE);
	len += pstr(tmp);
	len += pstr(RESET);
	ft_putchar('@');
	tmp = getenv("PWD");
	len += pstr(GREEN);
	len += pstr(tmp);
	len += pstr(CYAN);
	len += pstr(" > ");
	len += pstr(RESET);
	return (len);
}

char		*addchar(char *str, char c, int pos)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 2))))
		return (NULL);
	while (str[i])
	{
		if (i == pos)
		{
			new[j] = c;
			j++;
		}
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

void		print_rest(char *str, int pos)
{
	while (str[pos])
	{
		ft_putchar(str[pos]);
		pos++;
	}
}

int			left_space_on_line(t_bash data)
{
	ft_putnbr(data.column_count - data.prompt_len - data.iterator);
	return (data.column_count - data.prompt_len - data.iterator);
}

int			main(int argc, char **argv)
{
	char	*cm_cap;
	t_bash	data;
	
	(void)argc;
	(void)argv;
	if (!conf_term())
	{
		char *cl_cap = tgetstr("cl", NULL);
		tputs(cl_cap, 1, ft_putchar);
		hello();
		char *cmd_in = NULL;
		char *tmp = NULL;
		char *entry = NULL;
		char buff[4086];
		int read_ret = 0;
		data.iterator = 0;
		data.column_count = tgetnum("co");
		data.prompt_len = prompt();
		while (42)
		{
			read_ret = read(0, buff, 4);
			if (ft_strnequ(buff, "\033[A", 3))
				printf("UP ARROW\n");
			else if (ft_strnequ(buff, "\033[B", 3))
				printf("UP DOWN\n");
			else if (ft_strnequ(buff, "\033[C", 3))
			{
				if (data.iterator < ft_strlen(cmd_in))
				{
					data.iterator++;
					RIGHT;
				}
			}
			else if (ft_strnequ(buff, "\033[D", 3))
			{
				if (data.iterator)
				{
					data.iterator--;
					LEFT;
				}
			}
			else if (ft_strnequ(buff, "\n", 1))
			{
				data.iterator = 0;
				ft_putchar(buff[0]);
				data.prompt_len = prompt();
			}
			else if (ft_isprint(buff[0]))
			{
				tmp = (data.iterator) ? addchar(cmd_in, buff[0], data.iterator) : ft_strndup(buff, 1);
				ft_strdel(&cmd_in);
				cmd_in = ft_strdup(tmp);
				ft_strdel(&tmp);
				print_rest(cmd_in, data.iterator);
				data.iterator++;
				if (data.iterator < ft_strlen(cmd_in))
				{
					int len = ft_strlen(cmd_in);
					while (len > data.iterator)
					{
						LEFT;
						len--;
					}
				}
			}
			else
			{
				ft_putstr("Hello Mr Termcaps\n");
			}
		}
	}
	return (0);
}