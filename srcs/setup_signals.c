/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:02:40 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/15 20:07:21 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	custom_return(void)
{
	t_vect	*cmd;

	ft_putstr(tgetstr("ve", NULL));
	term_put(DOWN);
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
	g_data->prompt_len = prompt(g_data->env, 0);
}

/*
** SIGINT signal interrupts process
*/

static void	sigint_handler(int sig)
{
	custom_return();
	signal(sig, sigint_handler);
}

/*
** SIGSTP signal suspends process
*/

static void	sigtstp_handler(int sig)
{
	signal(sig, sigtstp_handler);
}

void		setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGCHLD, sigtstp_handler);
}

void		sig_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
