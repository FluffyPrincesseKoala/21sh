/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:22:41 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/24 13:48:29 by cylemair         ###   ########.fr       */
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

	old = getenv("PWD");
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
			{
				update_current_directory(env, pwd);
				ft_strdel(&pwd);
			}
		}
	}
}

void			change_directory(t_bash *data)
{
	char		*path;

	while (VECT->args)
	{
		if (ft_strequ(VECT->args->content, "cd"))
		{
			if ((VECT->args = VECT->args->next))
			{
				if (ft_strequ(VECT->args->content, "-"))
					path = getenv("OLDPWD");
				else
					path = VECT->args->content;
			}
			else
				path = getenv("HOME");
			if (path)
			{
				move_to_directory(data->env, path);
				return ;
			}
		}
		VECT->args = VECT->args->next;
	}
}