/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:41 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/26 21:38:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static int	is_file(const char *path)
{
	struct stat	sb;
	int ret;

	if (lstat(path, &sb) == -1)
		return (0);
	return (S_ISREG(sb.st_mode));
}

static void	update_current_directory(char **env, char *pwd)
{
	char		*old;
	char		*tmp;

	old = get_value_from_env(env, "PWD");
	tmp = ft_strjoin("OLDPWD=", old);
	if (env_key_exists(env, "OLDPWD"))
		env = change_value_in_array(env, "OLDPWD", tmp);
	else
		add_value_to_array(&env, tmp);
	ft_strdel(&tmp);
	tmp = ft_strjoin("PWD=", pwd);
	env = change_value_in_array(env, "PWD", tmp);
	ft_strdel(&tmp);
}

static void	move_to_directory(char **env, char *path)
{
	char		*pwd;
	char		buff[4096 + 1];

	if (!access(path, (F_OK & R_OK)))
	{
		if (!is_file(path) && chdir(path) == E_CHDIR)
			put_error_msg("cd : permission denied\n");
		else
		{
			if (!(pwd = getcwd(buff, 4096)))
				put_error_msg("cd : permission denied\n");
			else
				update_current_directory(env, pwd);
		}
	}
	else
		if (!is_file(path))
			put_error_msg("cd : no such file or directory\n");
		else
			put_error_msg("cd : permission denied\n");
}

void		change_directory(t_bash *data, t_vect *command)
{
	t_arg		*argument;
	char		*path;

	argument = command->args;
	if (ft_strequ(argument->content, "cd"))
	{
		if (argument->next && (argument = argument->next))
		{
			if (ft_strequ(argument->content, "-"))
				path = get_value_from_env(data->env, "OLDPWD");
			else
				path = argument->content;
		}
		else
			path = get_value_from_env(data->env, "HOME");
		if (path)
		{
			move_to_directory(data->env, path);
			return ;
		}
		else
			data->error = ENV_FAIL;
	}
}
