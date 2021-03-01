/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:59:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/19 19:24:14 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char			*use_shell_var(char **env, char *str)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	result = ft_strdup(str);
	while (var_name = ft_strchr(result, '$'))
	{
		var_name = ft_strsub(var_name, 0, ft_smallest_strichr(var_name, ':', ' '));
		var_value = get_env_var_value(env, var_name + 1);
		if (!var_value)
			var_value = "";
		result = ft_free_replaced_substr(result, var_name, var_value);
		ft_strdel(&var_name);
	}
	return (result);
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
