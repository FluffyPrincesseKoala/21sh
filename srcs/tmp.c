/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:00:02 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/28 14:50:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		puterror(int error)
{
	ft_putstr_fd(RED, 2);
	ft_putchar_fd(error, 2);
	ft_putstr_fd(RESET, 2);
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

int			prompt(int short_prompt)
{
	int		len;

	len = 0;
	if (!short_prompt)
	{
		pstr(BLUE);
		len += pstr(getenv("USER"));
		pstr(RESET);
		len += pchar('@');
		pstr(GREEN);
		len += pstr(getenv("PWD"));
		pstr(CYAN);
		len += pstr(" > ");
		pstr(RESET);
	}
	else
	{
		len += pstr(">");
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

int		lendelim(char *str, char delim, int start)
{
	int	i;

	i = 0;
	while (str && str[i + start] && str[i + start] != delim)
		i++;
	return (i);
}

char		*findenv(char **env, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = lendelim(var, '=', 0);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			return (*(env + i) + len + 1);
		i += 1;
	}
	return (NULL);
}

//oid		exec_onebyone(t_bash data)
//
//t_vect	*lst;
//char	*path;
////ft_putchar('\n');
//lst = (data.vector) ? data.vector : NULL;
//while (lst && !data.error)
//{
//	if ((path = build_path(data, lst)) && !access(path, X_OK))
//		exec_cmd(data, path, lst);
//	else if (lst->args && !access((const char*)lst->args->content, X_OK))
//		exec_cmd(data, lst->args->content, data.vector);
//	else
//		put_error(lst->args->content, UNOW);
//	lst = lst->next;
//}
//

int			pending_line(char *str)
{
	char	*separator;
	int		stack;
	int		i;
	int		j;

	i = 0;
	stack = 0;
	separator = ft_strdup("\'\"");
	while (separator[i])
	{
		j = 0;
		while (str && str[j])
		{
			if (str[j] == separator[i])
				stack += (stack) ? 1 : -1;
			j++;
		}
		if (stack)
			return (stack);
		i++;
	}
	return (stack);
}

void		loop(t_bash *data)
{
	char	buff[4086];
	int		is_key;

	is_key = 0;
	data->start_expend = 0;
	data->expend_up = 0;
	while (42)
	{
		read(0, buff, 6);
		if (ft_strnequ(buff, "\n", 1))
			handle_eol(data, buff);
		if (data->error)
			break;
		if (ft_strnequ(buff, "\033", 1) || buff[0] == 127)
			arrow_key(data, buff);
		else if (ft_isprint(buff[0]) || data->expend)
		{
			data->iterator = handle_new_entry(data, buff, data->iterator);
		}
		if (data->error)
			break;
	}
}
