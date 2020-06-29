/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/28 15:45:26 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*build_path(t_bash *data, t_vect *lst)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;
	int		ret;

	i = -1;
	tmp = NULL;
	tmp2 = NULL;
	paths = ft_strsplit(getenv("PATH"), ':');
	while (paths && paths[++i] && lst->args && lst->args->content)
	{
		tmp2 = ft_strjoin(paths[i], "/");
		tmp = (tmp2) ? ft_strjoin(tmp2, lst->args->content) : NULL;
		if (tmp && !(ret = access((const char*)tmp, F_OK)))
		{
			ft_strdel(&tmp2);
			free_array(paths);
			return (tmp);
		}
		ft_strdel(&tmp);ft_strdel(&tmp2);
	}
	ft_strdel(&tmp);ft_strdel(&tmp2);
	free_array(paths);
	return (NULL);
}

static void print_failed_fork_error(pid_t pid)
{
	ft_putstr_fd("fork failed at ", 2);
	ft_putnbr_fd((int)pid, 2);
	ft_putchar('\n');
	exit(-1);
}

static void	execute_command(t_bash *data, t_redirection *redirections,
	char *path, char **args_array)
{
	if (redirections)
		handle_redirections(data, redirections, 0);
	if (!data->error)
		execve(path, args_array, data->env);
	//if (command->redirections)
	//	restore_directions(command->redirections);
}

void		handle_fork(t_bash *data, t_vect *command)
{
	char **args_array;
	char *path;
	int		status;
	pid_t	cpid;

	while(command)
	{
		args_array = arg_to_array(data, command->args);
		path = build_path(data, command);
		cpid = fork();
		if (fork_failed(cpid))
			print_failed_fork_error(cpid);
		else if (is_child(cpid))
			execute_command(data, command->redirections, path, args_array);
		wait(&status);
		command = command->next;
		free_array(args_array);
		ft_strdel(&path);
	}
}
