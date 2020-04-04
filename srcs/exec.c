/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/27 20:21:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*build_path(t_bash data, t_vect *lst)
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
	while (paths && paths[++i])
	{
		tmp2 = ft_strjoin(paths[i], "/");
		tmp = (tmp2) ? ft_strjoin(tmp2, lst->arg[0]) : NULL;
		if (tmp && !(ret = access((const char*)tmp, F_OK)))
		{
			ft_strdel(&tmp2);
			free_array(paths);
			return (tmp);
		}
		ft_strdel(tmp);ft_strdel(tmp2);
	}
	ft_strdel(tmp);ft_strdel(tmp2)
	free_array(paths);
	return (NULL);
}

static void print_failed_fork_error(pid_t pid)
{
	ft_putstr_fd("fork failed at ", 2);
	ft_putnbr_fd((int)pid, 2);
	ft_putchar('\n');
	exit(-1)
}

static void	execute_command(t_bash data, char *path, t_vect *command)
{
	if handle_redirections(command->redirections, 0)
		execve(path, command->arg, data.env);
	restore_directions(command->redirections)
}

void		handle_fork(t_bash data, char *path, t_vect *cmd)
{
	int		status;
	pid_t	cpid;

	cpid = fork();
	if (fork_failed(cpid))
		print_failed_fork_error(pid);
	else if (is_child(cpid))
		execute_command(data, path, cmd);
	wait(&status);
}
