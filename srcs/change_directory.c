/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:41 by cylemair          #+#    #+#             */
/*   Updated: 2020/12/18 11:47:35 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int		is_file(const char *path)
{
	struct stat	sb;

	if (lstat(path, &sb) == -1)
		put_error_msg("lstat error\n");
	return (S_ISREG(sb.st_mode));
}

static void		update_current_directory(char **env, char *pwd)
{
	char		*old;
	char		*tmp;

	old = findenv(env, "PWD");
	tmp = ft_strjoin("OLDPWD=", old);
	env = change_array_value(env, "OLDPWD", tmp);
	ft_strdel(&tmp);
	tmp = ft_strjoin("PWD=", pwd);
	env = change_array_value(env, "PWD", tmp);
	ft_strdel(&tmp);
}

static void		move_to_directory(char **env, char *path)
{
	char		*pwd;
	char		buff[4096 + 1];

	if (!access(path, F_OK))
	{
		if (chdir(path) == E_CHDIR)
			put_error_msg(is_file(path) ?
				"cd : no such file or directory"
				:
				"cd : permission denied"
			);
		else
		{
			if (!(pwd = getcwd(buff, 4096)))
				put_error_msg("cd : permission denied");
			else
				update_current_directory(env, pwd);
		}
	}
}

void			change_directory(t_bash *data, t_vect *command)
{
	char		*path;

	while (command->args)
	{
		if (ft_strequ(command->args->content, "cd"))
		{
			if ((command->args = command->args->next))
			{
				if (ft_strequ(command->args->content, "-"))
					path = findenv(data->env, "OLDPWD");
				else
					path = command->args->content;
			}
			else
				path = findenv(data->env, "HOME");
			if (path)
			{
				move_to_directory(data->env, path);
				return ;
			}
		}
		command->args = command->args->next;
	}
}