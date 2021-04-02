/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:27:44 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:56:23 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	unconf_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_old_term);
}

static int	init_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
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
	return (0);
}

int	conf_term(void)
{
	if (!init_term())
	{
		if (tcgetattr(STDIN_FILENO, &g_old_term) == -1)
			return (-1);
		if (tcgetattr(STDIN_FILENO, &g_new_term) == -1)
			return (-1);
		g_new_term.c_lflag &= ~(ICANON | ECHO);
		g_new_term.c_cc[VMIN] = 1;
		g_new_term.c_cc[VTIME] = 0;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &g_new_term) == -1)
			return (-1);
		return (0);
	}
	return (-1);
}
