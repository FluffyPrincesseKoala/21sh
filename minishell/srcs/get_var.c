/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:59:31 by cylemair          #+#    #+#             */
/*   Updated: 2020/03/06 15:46:47 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**split_var(char **env, char *str)
{
	char		*tmp;
	char		**var;
	int			k;

	k = 0;
	var = ft_strsplit(str, ':');
	while (var[k])
	{
		if (ft_strchr(var[k], '$'))
		{
			tmp = findenv(env, ft_strchr(var[k], '$') + 1);
			ft_strdel(&var[k]);
			var[k] = ft_strdup((tmp) ? tmp : "");
		}
		k++;
	}
	var[k] = NULL;
	return (var);
}

static char		*use_shell_var(char **env, char *str)
{
	char		*tmp;
	char		*ret;
	char		**var;
	int			k;

	var = split_var(env, str);
	ret = NULL;
	k = array_len(var);
	while (k--)
	{
		tmp = ft_strjoin(var[k], ret);
		if (ret)
			ft_strdel(&ret);
		ret = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (k)
		{
			tmp = ft_strjoin(":", ret);
			ft_strdel(&ret);
			ret = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	free_array(var);
	return (ret);
}

void			get_var(t_vect **head, char **env)
{
	t_vect		*lst;
	char		*tmp;
	int			i;

	lst = NULL;
	if (head)
		lst = *head;
	while (lst)
	{
		i = -1;
		while (lst->arg[++i])
		{
			if (lst->arg[i] && ft_strchr(lst->arg[i], '$'))
			{
				tmp = use_shell_var(env, lst->arg[i]);
				ft_strdel(&lst->arg[i]);
				lst->arg[i] = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
		}
		lst = lst->next;
	}
}
