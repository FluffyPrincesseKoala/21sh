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

void		clean_screen(t_bash *data)
{
	CLEAR;
	prompt(data->env, 0);
	ft_putstr(LINE);
}

void		return_exit(t_bash *data)
{
	if (!LINE && data->expend)
	{
		data_g->x = 0;
		data_g->y = 0;
		if (data->is_here_doc)
		{
			// kill heredoc
			data->is_here_doc = 0;
		}
		// kill expend
		data->expend = 0;
		CDOWN;
		ft_putstr(tgetstr("cr", NULL));
		prompt(data_g->env, 0);
	}
	else if (!LINE)
	{
		ft_putendl("exit");
		unconf_term();
		free_bash(data);
		exit(0);
	}
	else
	{
		return ;
	}
}

int			prompt(char **env, int short_prompt)
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
		len += pstr(findenv(env , "PWD"));
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

char		*findenv(char **env, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = lendelim(var, '=', 0);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, len) && ft_strlen(env[i]) > len + 1)
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
		j = -1;
		while (str && str[++j])
		{
			if (str[j] == separator[i] && ((j && str[j - 1] != '\\')
			|| (j >= 2 && str[j - 1] == '\\' && str[j - 2] == '\\') || (!j)))
				stack += (stack) ? 1 : -1;
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
	char	buff[MAX_INPUT_SIZE];
	int		is_key;
	int		exit;

	is_key = 0;
	exit = 0;
	data->start_expend = 0;
	data->expend_up = 0;
	set_up_signals();
	while (42 && exit != -1)
	{
		read(0, buff, MAX_INPUT_SIZE);
		if (ft_strnequ(buff, "\n", 1))
			exit = handle_eol(&data);
		else if (!data->error && (ft_strnequ(buff, "\033", 1)
		|| buff[0] == 127 || buff[0] == '\017'
		|| buff[0] == '\002' || buff[0] == 4 || ft_strnequ(buff, "\f", 1)))
			arrow_key(data, buff);
		else if (!data->error && ft_isprint(buff[0])
			&& !ft_strnequ(buff, "\n", 1))
			data->iterator = handle_new_entry(data, buff, data->iterator);
	}
}
