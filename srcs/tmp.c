/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:00:02 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 20:25:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
		tputs(tgetstr("os", NULL), 1, pchar);
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
	pstr(BLUE);
	len += pstr(tmp);
	pstr(RESET);
	len += pchar('@');
	tmp = getenv("PWD");
	pstr(GREEN);
	len += pstr(tmp);
	pstr(CYAN);
	len += pstr(" > ");
	pstr(RESET);
	return (len);
}

int			left_space_on_line(t_bash data)
{
	ft_putnbr(data.column_count - data.prompt_len - data.iterator);
	return (data.column_count - data.prompt_len - data.iterator);
}

void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		ft_strdel(&array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

t_vect		*format_line(t_bash *data)
{
	t_vect	*new;
	char	*tmp;
	char	**table;
	int		i;

	i = -1;
	new = NULL;
	tmp = NULL;
	table = NULL;
	
	/*
	**	formating to create a vector
	**	printf("%sformating to create a vector%s\n", CYAN, RESET);
	*/
	if ((*data).vector->line)
		tmp = replace_delim((*data).vector->line, '\t', ' ');
	if (tmp)
		table = ft_strsplit(tmp, ' ');

	/*
	**	create unique vector (ne gere pas ';' '|' '<' ...etc)
	**	printf("%screate unique vector%s\n", CYAN, RESET);
	*/
	if (table)
	{
		(*data).vector->arg = copy_array(table);
		free_array(table);
	}
	//printf("%sPush history%s\n", CYAN, RESET);
	(*data).vector->down = vect_new(NULL, NULL);
	(*data).vector->down->up = (*data).vector;
	return ((*data).vector->down);
}

void		loop(t_bash data)
{
	char	buff[4086];
	char	*path;

	data.cmd_in = ft_strdup("");
	data.iterator = 0;
	data.column_count = tgetnum("co");
	data.prompt_len = prompt();
	data.vector = vect_new(NULL, NULL);
	while (42)
	{
		read(0, buff, 6);
		if (ft_strnequ(buff, "\033", 1) || buff[0] == 127)
			arrow_key(&data, buff);
		else if (ft_strnequ(buff, "\n", 1))
		{
			ft_putchar(buff[0]);
			data.vector = format_line(&data);
			if ((path = build_path(data, data.vector->up)))
			{
				if (!access(path, X_OK))
					exec_cmd(data, path, data.vector->up);
			}
			else if (!access((const char*)data.vector->up->arg[0], X_OK))
				exec_cmd(data, data.vector->up->arg[0], data.vector);			
			data.iterator = 0;
			data.prompt_len = prompt();
		}
		else if (ft_isprint(buff[0]))
			handle_new_entry(&data, buff);
	}
}