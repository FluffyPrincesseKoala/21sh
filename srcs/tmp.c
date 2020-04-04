/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:00:02 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/02 19:15:23 by cylemair         ###   ########.fr       */
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

char		**array_merge(char **array, char **add, int pos)
{
	int		j;
	int		i;
	int		k;
	char	**new;

	j = 0;
	i = 0;
	k = 0;
	if (!(new = malloc(sizeof(char*) * (array_len(array) + array_len(add)))))
		return (NULL);
	while (array[i])
	{
		if (i == pos)
		{
			while (add[j])
			{
				new[k] = ft_strdup(add[j]);
				j++;
				k++;
			}
		}
		else
		{
			new[k] = ft_strdup(array[i]);
			k++;
		}
		i++;
	}
	new[k] = NULL;
	return (new);
}

// char		**split_separator(char *line, char *separator)
// {
// 	char	**ret;
// 	char	**tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	tmp = ft_strsplit(line, separator[i]);
// 	while (separator[i])
// 	{
// 		j = 0;
// 		if (!tmp)
// 	}
// }

char		**array_ncpy(char **src, int size, int start)
{
	char	**new;
	int		l;


	if (!(new = malloc(sizeof(char*) * (size + 1))))
	return (NULL);
	l = 0;
	while (l != size)
	{
		new[l] = ft_strdup(src[start]);
		start++;
		l++;
	}
	new[l] = NULL;
	return (new);
}

t_vect		*new_arg(char **arg, t_vect *new)
{
	if (new->arg)
	{
		new = vect_add(&new, vect_new(arg, NULL));
		free_array(arg);
	}
	else if (new)
	{
		new->arg = copy_array(arg);
		free_array(arg);
	}
	return (new);
}

t_vect		*format_line(t_bash *data)
{
	t_vect	*new;
	char	*tmp;
	char	**tmpbis;
	char	**tmpbbis;
	char	**table;
	int		i;
	int		len;
	int l = 0;

	i = 0;
	new = NULL;
	tmp = NULL;
	tmpbis = NULL;
	tmpbbis = NULL;
	table = NULL;
	
	/*
	**	formating to create a vector
	**	printf("%sformating to create a vector%s\n", CYAN, RESET);
	*/
	if ((*data).vector->line)
		tmp = replace_delim((*data).vector->line, '\t', ' ');
	/*
	**	create unique vector (ne gere pas ';' '|' '<' ...etc)
	**	printf("%screate unique vector%s\n", CYAN, RESET);
	*/
	if (tmp)
	{
		if (array_len(table = ft_strsplit(tmp, ' ')))
		{
			new = vect_new(NULL, (*data).vector->line);
			(*data).count_separator = 0;
			while (table[i] && !(*data).error)
			{
				len = 0;
				while (table[i+len] && (table[i+len][0] != '|') && (table[i+len][0] != ';'))
					len++;
				if (len)
				{
					tmpbis = array_ncpy(table, len, i);
					new = new_arg(tmpbis, new);
					i += len;
				}
				else if (((table[i+len][0] == '|') || (table[i+len][0] == ';')) && !i)
				{
					ft_strdel(&(*data).error);
					(*data).error = ft_strjoin(SYNTAX, table[i+len]);
				}
				else
				{
					(*data).count_separator++;
					i++;
				}
			}
			free_array(table);
			new->up = (*data).vector->up;
			new->down = (*data).vector->down;
			if ((*data).vector)
				free_vector(&(*data).vector);
			(*data).vector = new;
		}
	}
	(*data).vector->down = vect_new(NULL, NULL);
	(*data).vector->down->up = (*data).vector;
	(*data).vector = (*data).vector->down;
	ft_strdel(&tmp);
	return ((*data).vector);
}

void		loop(t_bash data)
{
	char	buff[4086];
	char	*path;
	t_vect	*lst;

	data.cmd_in = ft_strdup("");
	data.error = NULL;
	while (42)
	{
		read(0, buff, 6);
		if (ft_strnequ(buff, "\033", 1) || buff[0] == 127)
			arrow_key(&data, buff);
		else if (ft_strnequ(buff, "\n", 1))
		{
			ft_putchar(buff[0]);
			if (data.vector->line && ONLY_WCHAR)
			{
				data.vector = format_line(&data);
				lst = (data.vector->up->arg) ? data.vector->up : NULL;
				while (lst && !data.error)
				{
					if ((path = build_path(data, lst)) && !access(path, X_OK))
						exec_cmd(data, path, lst);
					else if (lst->arg && !access((const char*)lst->arg[0], X_OK))
						exec_cmd(data, lst->arg[0], data.vector);
					else
					{
						pstr(RED);
						pstr(lst->arg[0]);
						pstr(" : ");
						pstr("Command not found\n");
						pstr(RESET);
					}
					lst = lst->next;
				}
				if (data.error)
				{
					pstr(RED);
					pstr(data.error);
					pstr("\n");
					pstr(RESET);
					ft_strdel(&data.error);
				}
			}
			data.iterator = 0;
			data.prompt_len = prompt();
		}
		else if (ft_isprint(buff[0]))
			data.iterator = handle_new_entry(&data, buff, data.iterator);
	}
}
