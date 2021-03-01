/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/19 17:23:06 by cylemair         ###   ########.fr       */
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

static char	*build_command_path(char *env_path, char *command_name)
{
	char *command_path;

	if (!(command_path = ft_strjoin(env_path, "/")))
		return (NULL);
	if (!(command_path = ft_strjoin_free(&command_path, &command_name, 1)))
		return (NULL);
	return (command_path);
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
	struct stat sb;
	char	*path;

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

static		size_t  args_len(t_arg *arg)
{
    size_t len;

    len = 0;
    while (arg)
    {
        if (CONTENT)
            len++;
        arg = arg->next;
    }
    return len;
}

/*
** Convert the contents of a chained list of t_arg to an array of string.
*/

char    	**arg_to_array(t_bash *data, t_arg *arg)
{
    char    **array;
    int     i;

    if (!(array = malloc(sizeof(char*) * (args_len(arg) + 1))))
        data->error = MALLOC_ERROR;
    else
    {
        i = 0;
        while (arg)
        {
            if (CONTENT)
            {
                array[i] = ft_strdup(CONTENT);
                i++;
            }
            arg = arg->next;
        }
        array[i] = NULL;
    }
    return (array);
}