/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 13:04:17 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains execution pre-processing functions generic to all kind of
** commands.
*/

/*
** Execute the redirections, set up earlier, right before executing the command.
** If it's a builtin, use the appropriate custom function, otherway use execve.
*/

void        execute_command(t_bash *data, t_vect *command)
{
        if (command->redirections)
            execute_redirections(data, command->redirections);
        if (command->builtin)
        {
            if (!data->error)
                command->builtin(data, command);
            restore_directions(command->redirections);
        }
        else
            execute_syscall(data, command);
}

int        handle_execution(t_bash *data, t_vect *command)
{
    if (handle_pipe(data, command) == FAIL)
        return (FAIL);
    handle_heredoc(data, command);
    execute_command(data, command);
    return (SUCCESS);
}

/*
** After setting fields in the command structure, handle its execution inside
**  or outside a fork.
*/

static int  handle_command(t_bash *data, t_vect *command)
{
    int     status;
    pid_t   cpid;

    unconf_term();
    if (set_up_command_redirections(data, command) == FAIL)
        return (FAIL);
    search_built_in(data, command);
    if (fork_is_required(command))
    {
        cpid = fork();
        if (fork_failed(cpid))
            print_failed_fork_error(cpid);
        else if (is_child(cpid))
            if (handle_execution(data, command) == FAIL)
            {
                error_code_to_message(&data->error);
                exit(EXIT);
            }
        wait(&status);
    }
    else
        if (handle_execution(data, command) == FAIL)
            return (FAIL);
    return (SUCCESS);
}

/*
** Loop on each submitted command to process all steps of its execution.
** Piped commands are executed concomitantly.
*/

int         handle_commands(t_bash *data, t_vect *command)
{
    while (command)
    {
        if (is_exit(command))
            return (EXIT);
        if (handle_command(data, command) == FAIL)
            return (FAIL);
	    while (command_is_piped(command))
	    	command = command->next;
	    command = command->next;
    }
    return (SUCCESS);
}