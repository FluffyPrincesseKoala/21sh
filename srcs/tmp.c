/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:00:02 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/24 16:11:18 by cylemair         ###   ########.fr       */
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
	SAVE_C;
	return (len);
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

char		**array_ncpy(char **src, int size, int start)
{
	char	**new;
	int		i;


	if (!(new = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = 0;
	while (i != size)
	{
		new[i] = ft_strdup(src[start]);
		start++;
		i++;
	}
	new[i] = NULL;
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

int			next_delim(char **array, int start)
{
	int		len;

	len = 0;
	while (array && array[start + len]
		&& array[start + len][0] != '|' && array[start + len][0] != ';')
	{
		len++;
	}
	return (len);
}

void		put_error(char *str, char *type)
{
	ft_putstr_fd(RED, 2);
	if (type)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(type, 2);
	}
	else
		ft_putendl_fd(str, 2);
	ft_putstr_fd(RESET, 2);
}

t_vect		*read_separator(char **table, t_bash *data)
{
	t_vect *new;
	char	**tmp;
	int		len;
	int		i;

	i = 0;
	new = vect_new(NULL, data->vector->line);
	while (table[i] && !data->error)
	{
		if ((len = next_delim(table, i)))
		{
			tmp = array_ncpy(table, len, i);
			new = new_arg(tmp, new);
			i += len;
		}
		else if (((table[i+len][0] == '|') || (table[i+len][0] == ';')) && !i)
		{
			ft_strdel(&data->error);
			data->error = ft_strjoin(SYNTAX, table[i+len]);
		}
		else
			i++;
	}
	return (new);
}

t_vect		*format_line(t_bash *data)
{
	t_vect	*new;
	char	*tmp;
	char	*lol;
	char	**table;

	new = NULL;
	tmp = NULL;
	lol = NULL;
	table = NULL;
	
	/*
	**	formating to create a vector
	**	printf("%sformating to create a vector%s\n", CYAN, RESET);
	*/
	if (data->vector->line)
	{
		lol = replace_substr(data->vector->line, ";", " ; ");
		tmp = replace_substr((lol) ? lol : data->vector->line, "|", " | ");
		ft_strdel(&lol);
	}
	/*
	**	create unique vector (ne gere pas ';' '|' '<' ...etc)
	**	printf("%screate unique vector%s\n", CYAN, RESET);
	*/
	if (tmp)
	{
		if (array_len(table = ft_strsplit(tmp, ' ')))
		{
			new = read_separator(table, data);
			free_array(table);
			new->up = data->vector->up;
			new->down = data->vector->down;
			if (data->vector)
				free_vector(&data->vector);
			data->vector = new;
		}
	}
	data->vector = link_history(&data->vector, vect_new(NULL, NULL));
	ft_strdel(&tmp);
	return (data->vector);
}

static void		exec_onebyone(t_bash data)
{
	t_vect	*lst;
	char	*path;

	lst = (data.vector->up->arg) ? data.vector->up : NULL;
	while (lst && !data.error)
	{
		if ((path = build_path(data, lst)) && !access(path, X_OK))
			exec_cmd(data, path, lst);
		else if (lst->arg && !access((const char*)lst->arg[0], X_OK))
			exec_cmd(data, lst->arg[0], data.vector);
		else
			put_error(lst->arg[0], UNOW);
		lst = lst->next;
	}
}

void		loop(t_bash *data)
{
	char	buff[4086];

	while (42)
	{
		read(0, buff, 6);
		if (ft_strnequ(buff, "\033", 1) || buff[0] == 127)
			arrow_key(data, buff);
		else if (ft_strnequ(buff, "\n", 1))
		{
			ft_putchar(buff[0]);
			if (data->vector->line && (count_delim(LINE, ' ') != ft_strlen(LINE)))
			{
				data->vector = format_line(data);
				exec_onebyone((*data));
				if (data->error)
				{
					put_error(data->error, NULL);
					ft_strdel(&data->error);
				}
			}
			data->iterator = 0;
			data->prompt_len = prompt();
		}
		else if (ft_isprint(buff[0]))
			data->iterator = handle_new_entry(data, buff, data->iterator);
	}
}

// void		debug_loop_try_termcaps(t_bash data)
// {
// 	char	buff[4086];

// 	data.error = NULL;
// 	while (42)
// 	{
// 		data.column_count = MAX_X;
// 		read(0, buff, 6);
// 		if (ft_strnequ(buff, "\033", 1) || buff[0] == 127)
// 			arrow_key(&data, buff);
// 		else if (ft_strnequ(buff, "\n", 1))
// 		{
// 			if (data.vector->line && ONLY_WCHAR)
// 			{
// 				data.vector = format_line(&data);
// 				tputs(tgoto(tgetstr(data.vector->up->line, NULL), 0 , 0), 1, &pchar);
// //				exec_onebyone(data);
// 			}
// 			data.iterator = 0;
// 			data.prompt_len = prompt();
// 		}
// 		else if (ft_isprint(buff[0]))
// 			data.iterator = handle_new_entry(&data, buff, data.iterator);
// 	}
// }
