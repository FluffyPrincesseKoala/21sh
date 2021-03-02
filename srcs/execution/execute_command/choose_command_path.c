/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 18:34:34 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions specific to syscall execution, using execve, and
** binary path finding.
*/

/*
** Join given path with the command name, but separate them by a '\'.
*/

static char	*build_command_path(char *env_path, char *cmd_name)
{
	char *cmd_path;

	if (!(cmd_path = ft_strjoin(env_path, "/")))
		return (NULL);
	if (!(cmd_path = ft_strjoin_free(&cmd_path, &cmd_name, FREE_S1)))
		return (NULL);
	return (cmd_path);
}

/*
** Search for a binary with the command name in env paths.
** Make sure the resulting file has execution and read permissions.
*/

static char	*get_command_path_from_env(char **env, char *command_name)
{
	int		i;
	char	*command_path;
	char	**env_paths;

	i = 0;
	env_paths = ft_strsplit(get_env_var_value(env, "PATH"), ':');
	while (env_paths && env_paths[i] && command_name)
	{
		command_path = build_command_path(env_paths[i], command_name);
		if (command_path && !access(command_path, F_OK | X_OK | R_OK))
		{
			free_array(env_paths);
			return (command_path);
		}
		ft_strdel(&command_path);
		i++;
	}
	free_array(env_paths);
	return (NULL);
}

/*
** To be considered as a path, the name should start with a path location and
**  the resulting file should exist with execution and read permissions.
*/

static int	path_is_given(char *name)
{
	if ((ft_strnequ(name, "./", 2) || ft_strnequ(name, "../", 3)
		|| ft_strnequ(name, "/", 1)) && !access(name, F_OK | X_OK | R_OK))
		return (TRUE);
	else
		return (FALSE);
}

/*
** Is user submitted the whole path, copy it.
** Otherway get it from env.
** Make sure we have a valid path.
*/

char		*choose_command_path(t_bash *data, char *command_name)
{
	struct stat	sb;
	char		*path;

	path = NULL;
	if (path_is_given(command_name))
		path = ft_strdup(command_name);
	else
		path = get_command_path_from_env(data->env, command_name);
	if (!path || (lstat(path, &sb) == 0 && S_ISDIR(sb.st_mode)))
	{
		put_error_msg(command_name);
		put_error_msg(UNOW);
		return (NULL);
	}
	return (path);
}
