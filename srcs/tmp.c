/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:00:02 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/29 17:20:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		put_error_msg(char *error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(RESET, 2);
}

void		puterror(int error)
{
	ft_putstr_fd(RED, 2);
	ft_putnbr_fd(error, 2);
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

int							conf_term()
{
	if (!init_term())
	{
		if (tcgetattr(STDIN_FILENO, &old_term) == -1)
			return (-1);
		if (tcgetattr(STDIN_FILENO, &new_term) == -1)
			return (-1);
		new_term.c_lflag &= ~(ICANON|ECHO);
		new_term.c_cc[VMIN] = 1;
		new_term.c_cc[VTIME] = 0;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1)
			return (-1);
		//tputs(tgetstr("os", NULL), 1, pchar);
	}
	else
		return (-1);
	return (0);
}

void					unconf_term()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	ft_putendl_fd("Bye!", STDOUT_FILENO);
}

void		hello()
{
	struct winsize	w;
	int		column_count;
	int		i = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	column_count = w.ws_col;
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

	if (short_prompt == 1)
	 return (0);
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
	else if (short_prompt == -1)
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

	i = (str[start] == delim) ? 1 : 0;
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
		{
			ft_strdel(&separator);
			return (stack);
		}
		i++;
	}
	ft_strdel(&separator);
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
		if (ft_strnequ(LINE, "exit", 4))
		{
			info("Mélol");
			unconf_term();
			exit(0);
		}
		if (ft_strnequ(buff, "\n", 1))
			handle_eol(data, buff);
		else if (!data->error && (ft_strnequ(buff, "\033", 1)
		|| buff[0] == 127 || buff[0] == '\017' || buff[0] == '\002'))
			arrow_key(data, buff);
		else if (!data->error && ft_isprint(buff[0]) && !ft_strnequ(buff, "\n", 1))
			data->iterator = handle_new_entry(data, buff, data->iterator);
		if (data->error)
			break;
	}
}
