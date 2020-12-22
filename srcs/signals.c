/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 19:43:19 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 19:43:58 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		custom_return(void)
{
	CDOWN;
	ft_putstr(tgetstr("cr", NULL));
	prompt(data_g->env, 0);
	data_g->x = 0;
	data_g->x = 0;
	data_g->iterator = 0;
	if (data_g->vector->down)
	{
		while (data_g->vector->down)
			data_g->vector = data_g->vector->down;
	}
	else
		ft_strdel(&data_g->vector->line);
}

/*
* SIGINT signal interrupts process 
*/
static void sigint_handler(int sig)
{
    signal(sig, sigint_handler);
	custom_return();
}

/*
* SIGSTP signal suspends process
*/
static void sigtstp_handler(int sig)
{
    signal(sig, sigtstp_handler);
}

/*
* SIGCHLD signal is sent to parent process when child process dies
*/
static void sigchld_handler(int sig)
{
    signal(sig, sigchld_handler);
}

void        set_up_signals()
{
    signal(SIGINT, &sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGCHLD, sigchld_handler);
}