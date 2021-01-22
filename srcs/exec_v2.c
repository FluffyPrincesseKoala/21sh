/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/22 12:26:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** Find the path to the command binary file.
** Convert the args chained list to an array.
** Call execve with those params.
*/

void        execute_syscall(t_bash *data, t_vect *command)
{
    ft_strdel(&(data->path));
    if (data->path = choose_path(command->args->content, command, data))
    {
        free_array(data->args_array);
        data->args_array = arg_to_array(data, command->args);
        execve(data->path, data->args_array, data->env);
    }
}

/*
** Execute the redirections, set up earlier, right before executing the command.
** If it's a builtin, use the appropriate function, otherwise use execve.
*/

void        execute_command(t_bash *data, t_vect *command)
{
        if (command->redirections)
            execute_redirections(data, command->redirections, 0);
        if (command->builtin)
        {
            command->builtin(data, command);
            restore_directions(command->redirections);
        }
        else
            execute_syscall(data, command);
}

void        handle_execution(t_bash *data, t_vect *command)
{
    handle_pipe(data, command);
    handle_heredoc(data, command);
    execute_command(data, command);
}

/*
** After setting fields in the command structure, handle its execution inside
** or outside a fork.
*/

int			handle_command(t_bash *data, t_vect *command)
{
    int     status;
    pid_t   cpid;

    unconf_term();
    search_redirections_in_cmd(data, command);
    search_built_in(data, command);
    if (fork_is_required(command))
    {
        cpid = fork();
        if (fork_failed(cpid))
            print_failed_fork_error(cpid);
        else if (is_child(cpid))
            handle_execution(data, command);
        wait(&status);
    }
    else
        handle_execution(data, command);    
    reset_conf_term();
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
        handle_command(data, command);
	    while (command_is_piped(command))
	    	command = command->next;
	    command = command->next;
    }
    return (SUCCESS);
}