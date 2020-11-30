/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/25 18:23:44 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	free_two_var_to_feet_norm(char **a, char **b)
{
	ft_strdel(a);
	ft_strdel(b);
}

char		*build_path(char **env, t_vect *lst)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;
	int		ret;

	i = -1;
	tmp = NULL;
	tmp2 = NULL;
	paths = ft_strsplit(findenv(env, "PATH"), ':');
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
		free_two_var_to_feet_norm(&tmp, &tmp2);
	}
	free_two_var_to_feet_norm(&tmp, &tmp2);
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

static char *choose_path(char *name, t_vect *cmd, t_bash *data)
{
	char	*path;

	path = NULL;
	if (ft_strnequ(name, "./", 2) || (ft_strnequ(name, "../", 3)))
		path = ft_strdup(name);
	else
		path = build_path(data->env, cmd);
	if (!path)
	{
		put_error_msg(name);
		put_error_msg(UNOW);
	}
	return (path);
}

static void handle_pipe(t_bash *data, t_vect *command)
{
	char			**args_array;
	char			*path;
	int				pipe_fd[2];
	int				status;
	pid_t			cpid;
    t_redirection   *new;

	pipe(pipe_fd);
	cpid = fork();
	if (fork_failed(cpid))
		print_failed_fork_error(cpid);
	else if (is_child(cpid))
	{
		close(pipe_fd[1]);
		command = command->next;
		args_array = arg_to_array(data, command->args);
		new = new_redirection(command, 0);
		new->left_fd = 0;
		new->right_fd = pipe_fd[0];
		if ((path = choose_path(*args_array, command, data)))
			execute_command(data, command, args_array);
		else
			exit(-1);
	}
	else
	{
		close(pipe_fd[0]);
		new = new_redirection(command, 0);
		new->left_fd = 1;
		new->right_fd = pipe_fd[1];
	}
}

static void	execute_command(t_bash *data, t_vect *command, char **args_array)
{
	char	*path;

	if (command->separator == '|')
		handle_pipe(data, command);
	if (command->redirections)
		handle_redirections(data, command->redirections, 0);
	if ((path = choose_path(*args_array, command, data)) && !data->error)
	{
		if (execve(path, args_array, data->env) == -1)
			exit(-1);
	}
	else
		exit(-1);
	//if (command->redirections)
	//	restore_directions(command->redirections);
}

void		handle_fork(t_bash *data, t_vect *command)
{
	char 	**args_array;
	char 	*path;
	int		status;
	pid_t	cpid;

	while(command)
	{
		args_array = arg_to_array(data, command->args);
		if ((path = choose_path(*args_array, command, data)))
		{		
			cpid = fork();
			if (fork_failed(cpid))
				print_failed_fork_error(cpid);
			else if (is_child(cpid))
				execute_command(data, command, args_array);
			wait(&status);
		}
		while (command->separator == '|')
			command = command->next;
		command = command->next;
		free_array(args_array);
		ft_strdel((path) ? &path : NULL);
	}
	// fork();
	// int p[2];
	// pipe(p);
	// fork();
	// enfant: <p[0]
	// execute
	// parent: 1>p[1]
	// execute
}
