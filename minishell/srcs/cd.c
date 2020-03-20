/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:57:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 20:19:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_file(const char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		puterror("lstat error\n");
	return (S_ISREG(sb.st_mode));
}

void			change_dir(const char *path, t_sh *ell)
{
	char		*cwd;
	char		buff[4096 + 1];

	if (!access(path, F_OK))
	{
		if (chdir(path) == E_CHDIR)
			puterror(is_file(path) ? NODIR : DENY);
		else
		{
			if (!(cwd = getcwd(buff, 4096)))
				puterror(DENY);
			(*ell).env = update_key((*ell).env, "PWD=", cwd, "OLDPWD=");
		}
	}
	else
	{
		puterror((char*)path);
		puterror(": ");
		puterror(NOFOD);
	}
}
