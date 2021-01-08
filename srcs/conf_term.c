/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:27:44 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/08 15:39:26 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int         init_term()
{
	int     ret;
	char    *term_type = getenv("TERM");

	if (term_type == NULL)
	{
		put_error_msg(E_TERM_SET);
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		put_error_msg(E_TERM_CAP);
		return (-1);
	}
	else if (ret == 0)
	{
		put_error_msg(E_TERM_DEF);
		return (-1);
	}
	return 0;
}

int         conf_term()
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
    	return (0);
	}
	return (-1);
}

void	    unconf_term()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
//	ft_putendl_fd("Bye!", STDOUT_FILENO);
}

void		reset_conf_term()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}