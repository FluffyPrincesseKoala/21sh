/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:02:40 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/11 19:08:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	custom_return(void)
{
	t_vect	*cmd;

	term_put(DOWN);
	ft_putstr(tgetstr("cr", NULL));
	prompt(g_data->env, 0);
	g_data->x = 0;
	g_data->y = 0;
	g_data->is_heredoc = 0;
	g_data->iterator = 0;
	g_data->history_stack = 0;
	g_data->expend = 0;
	if ((cmd = g_data->vector))
	{
		while (cmd && cmd->down)
			cmd = cmd->down;
		ft_strdel(&cmd->line);
		free_array(cmd->doc_string);
	}
}

/*
** SIGINT signal interrupts process
*/

static void	sigint_handler(int sig)
{
	signal(sig, sigint_handler);
	custom_return();
}

/*
** SIGSTP signal suspends process
*/

static void	sigtstp_handler(int sig)
{
	signal(sig, sigtstp_handler);
}

/*
** SIGCHLD signal is sent to parent process when child process dies
*/

static void	sigchld_handler(int sig)
{
	signal(sig, sigchld_handler);
}

void		setup_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGCHLD, sigchld_handler);
}
