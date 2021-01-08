/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/08 18:32:24 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void        execute_syscall(t_bash *data, t_vect *command)
{
    if (data->path)
        ft_strdel(&(data->path));
    if (data->path = choose_path(command->args->content, command, data))
    {
        free_array(data->args_array);
        data->args_array = arg_to_array(data, command->args);
        execve(data->path, data->args_array, data->env);
    }
}

void        execute_command(t_bash *data, t_vect *command)
{
        if (command->redirections)
            handle_redirections(data, command->redirections, 0);
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
    if (using_heredoc(command))
        handle_heredoc(data, command);
    else
    {
        execute_command(data, command);
    }    
}

int			new_handle_command(t_bash *data, t_vect *command, int forked)
{
    int     status;
    pid_t   cpid;

    unconf_term();
    search_redirections_in_cmd(data, command);
    search_built_in(data, command);
    if (!forked && fork_is_required(command))
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

int         handle_commands(t_bash *data, t_vect *command)
{
    while (command)
    {
        if (is_exit(command))
            return (EXIT);
        new_handle_command(data, command, FALSE);
	    while (command_is_piped(command))
	    	command = command->next;
	    command = command->next;
    }
    return (SUCCESS);
}