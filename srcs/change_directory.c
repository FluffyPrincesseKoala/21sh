/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:41 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/19 17:23:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	is_file(const char *path)
{
	struct stat	sb;

	if (lstat(path, &sb) == -1)
		put_error_msg("lstat error\n");
	return (S_ISREG(sb.st_mode));
}

static void	update_current_directory(char **env, char *pwd)
{
	char		*old;
	char		*tmp;

	old = get_env_var_value(env, "PWD");
	tmp = ft_strjoin("OLDPWD=", old);
	if (is_env_key_exist(env, "OLDPWD="))
		env = change_array_value(env, "OLDPWD", tmp);
	else
		env = array_add_value(env, tmp);
	ft_strdel(&tmp);
	tmp = ft_strjoin("PWD=", pwd);
	env = change_array_value(env, "PWD", tmp);
	ft_strdel(&tmp);
}

static void	move_to_directory(char **env, char *path)
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

void		change_directory(t_bash *data, t_vect *command)
{
	t_arg		*argument;
	char		*path;

	argument = command->args;
	if (ft_strequ(argument->content, "cd"))
	{
		if ((argument = argument->next))
		{
			if (ft_strequ(argument->content, "-"))
				path = get_env_var_value(data->env, "OLDPWD");
			else
				path = argument->content;
		}
		else
			path = get_env_var_value(data->env, "HOME");
		if (path)
		{
			move_to_directory(data->env, path);
			return ;
		}
		else
			data->error = ENV_FAIL;
	}
}