/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:53:40 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 20:03:02 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(t_sh *ell, t_vect *cmd)
{
	(void)cmd;
	putab((*ell).env);
}

void		builtin_unsetenv(t_sh *ell, t_vect *cmd)
{
	char	**tab;

	if (cmd->arg[1])
	{
		tab = delenv((*ell).env, cmd->arg[1]);
		if (((*ell).env != (*ell).venv) && array_cmp((*ell).env, tab))
			free_array((*ell).env);
		(*ell).env = tab;
	}
}

void		builtin_setenv(t_sh *ell, t_vect *cmd)
{
	char	*tmp;
	char	*tmpbis;
	char	**tab;
	int		i;

	i = 0;
	tmp = NULL;
	tmpbis = NULL;
	while (cmd->arg[i])
		i++;
	if (i > 2)
	{
		tmpbis = ft_strjoin(cmd->arg[1], "=");
		tmp = ft_strjoin(tmpbis, cmd->arg[2]);
	}
	else if (i != 2)
		return ;
	else
		tmp = ft_strjoin(cmd->arg[1], "=");
	tab = change_key((*ell).env, tmp);
	if ((*ell).env != (*ell).venv)
		free_array((*ell).env);
	(*ell).env = tab;
	ft_strdel(&tmp);
	ft_strdel(&tmpbis);
}

void		builtin_cd(t_sh *ell, t_vect *cmd)
{
	char	*tmp;
	char	*tmpbis;
	int		i;

	i = 0;
	tmp = NULL;
	tmpbis = NULL;
	while (cmd->arg[i])
		i++;
	if (i > 1 && !ft_strcmp(cmd->arg[1], "-"))
	{
		tmp = ft_strdup(findenv((*ell).env, "OLDPWD="));
		tmpbis = ft_strjoin("/", tmp);
		streplace((&cmd->arg[1]), &tmpbis);
		ft_strdel(&tmp);
		ft_strdel(&tmpbis);
	}
	if (i == 1)
	{
		tmp = ft_strdup(findenv((*ell).env, "HOME="));
		change_dir(tmp, ell);
		ft_strdel(&tmp);
	}
	else
		change_dir(cmd->arg[1], ell);
}

void		builtin_echo(t_sh *ell, t_vect *cmd)
{
	int		i;
	int		j;

	i = 0;
	(void)ell;
	while (cmd->arg[++i])
	{
		if (i >= 2)
			ft_putchar(' ');
		j = -1;
		while (cmd->arg[i][++j])
		{
			if ((cmd->arg[i][j] == '\\' || cmd->arg[i][j] == '\"'
				|| cmd->arg[i][j] == '\'')
				&& (j && cmd->arg[i][j - 1] == '\\'))
				ft_putchar(cmd->arg[i][j]);
			else if (cmd->arg[i][j] != '\\' && cmd->arg[i][j] != '\"'
					&& cmd->arg[i][j] != '\'')
				ft_putchar(cmd->arg[i][j]);
		}
	}
	ft_putchar('\n');
}
