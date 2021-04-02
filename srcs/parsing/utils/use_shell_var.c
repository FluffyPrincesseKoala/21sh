/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_shell_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:59:31 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:14:38 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

char	*use_shell_var(char **env, char *str)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	result = ft_strdup(str);
	var_name = ft_strchr(result, '$');
	while (var_name)
	{
		var_name = ft_strsub(var_name, 0, ft_smallest_strichr(var_name, " :'"));
		var_value = get_value_from_env(env, var_name + 1);
		if (!var_value)
			var_value = "";
		result = ft_free_replaced_substr(result, var_name, var_value);
		ft_strdel(&var_name);
		var_name = ft_strchr(result, '$');
	}
	return (result);
}
