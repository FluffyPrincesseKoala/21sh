/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/29 16:01:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	free_two_var_to_feet_norm(char **a, char **b)
{
	ft_strdel(a);
	ft_strdel(b);
}

char		*build_path(t_bash data, t_vect *lst)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;
	int		ret;

	i = -1;
	tmp = NULL;
	tmp2 = NULL;
	paths = ft_strsplit(getenv("PATH"), ':');
	while (paths && paths[++i] && lst->args->content)
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

int			exec_cmd(t_bash data, char *path, t_vect *cmd)
{
	int		status;
	char	**arg;
	pid_t	cpid;

	arg = lst_to_array(cmd->args);
	cpid = fork();
	if (cpid < 0)
	{
		ft_putstr_fd("fork faild at ", 2);
		ft_putnbr_fd((int)cpid, 2);
		ft_putchar('\n');
		exit(-1);
	}
	else if (cpid == 0)
		execve(path, arg, data.env);
	wait(&status);
	free_array(arg);
	return ((status < 0) ? -1 : 0);
}
