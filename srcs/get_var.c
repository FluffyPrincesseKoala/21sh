/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:59:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 17:55:31 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char		**split_var(char **env, char *str)
{
	char		*tmp;
	char		**var;
	int			k;

	k = 0;
	var = ft_strsplit(str, ':');
	while (var[k])
	{
		if (ft_strchr(var[k], '$')
		&& ft_strlen((ft_strchr(var[k], '$') + 1)) >= 1)
		{
			tmp = get_var_from_env(env, ft_strchr(var[k], '$') + 1);
			ft_strdel(&var[k]);
			var[k] = ft_strdup((tmp) ? tmp : "");
		}
		k++;
	}
	var[k] = NULL;
	return (var);
}

char		*use_shell_var(char **env, char *str)
{
	char		*tmp;
	char		*ret;
	char		**var;
	int			k;

	var = split_var(env, str);
	ret = NULL;
	k = ft_arraylen(var);
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

void			get_var(t_arg **head, char **env)
{
	t_arg		*arg;
	char		*tmp;

	arg = NULL;
	if (head)
		arg = *head;
	while (arg)
	{
		if (arg && CONTENT && ft_strchr(CONTENT, '$'))
		{
			tmp = use_shell_var(env, CONTENT);
			ft_strdel(&CONTENT);
			CONTENT = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		arg = arg->next;
	}
}

void		get_tilt(t_arg **head, char **env)
{
	t_arg		*arg;
	char		*tmp;
	char		*path_to_home;

	int i = 0;
	arg = NULL;
	if (head)
		arg = *head;
	while (arg)
	{
		if (CONTENT && ft_strchr(CONTENT, '~'))
		{
			path_to_home = get_var_from_env(env, "HOME");
			tmp = replace_substr(CONTENT, "~", path_to_home);
			ft_strdel(&CONTENT);
			CONTENT = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		arg = arg->next;
	}
}