/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/12 12:23:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** This file contains functions specific to syscall execution, using execve, and
** binary path finding.
*/

/*
** Join given path with the command name, but separate them by a '\'.
*/
char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if ((new = malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[i] = (char)s1[i];
		i += 1;
	}
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char		*kikoo(char **s1, char **s2, int s_to_free)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = NULL;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(*s2) + 1))))
		return (NULL);
	while (*s1 && (*s1)[i])
	{
		ret[i] = (char)(*s1)[i];
		i += 1;
	}
	while (*s2 && (*s2)[j])
		ret[i++] = (*s2)[j++];
	ret[i] = '\0';
	if (s_to_free == FREE_S1 || s_to_free == FREE_BOTH)
		ft_strdel(s1);
	if (s_to_free == FREE_S2 || s_to_free == FREE_BOTH)
		ft_strdel(s2);
	return (ret);
}

static char	*build_command_path(char *env_path, char *cmd_name)
{
	char *cmd_path;

	if (!(cmd_path = ft_strjoin(env_path, "/")))
		return (NULL);
	if (!(cmd_path = kikoo(&cmd_path, &cmd_name, FREE_S1)))
	{
		ft_strdel(&cmd_path);
		return (NULL);
	}
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
	env_paths = ft_strsplit(get_value_from_env(env, "PATH"), ':');
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
		|| ft_strnequ(name, "/", 1)) && !access(name, F_OK | X_OK | R_OK)
		&& !ft_strequ(name, ".") && !ft_strequ(name, ".."))
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
	else if (!ft_strequ(command_name, ".") && !ft_strequ(command_name, ".."))
		path = get_command_path_from_env(data->env, command_name);
	if (!path || (lstat(path, &sb) == 0 && S_ISDIR(sb.st_mode)))
	{
		put_error_msg(command_name);
		put_error_msg(UNOW);
		return (NULL);
	}
	return (path);
}
