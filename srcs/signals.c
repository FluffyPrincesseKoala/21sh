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

/*
* SIGINT signal interrupts process 
*/
static void sigint_handler(int sig)
{
    signal(sig, sigint_handler);
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
    ft_putendl(RED);
    ft_putendl("It's over now");
    ft_putendl(RESET);
    signal(sig, sigchld_handler);
}

void        set_up_signals()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGCHLD, sigchld_handler);
}