/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:53:23 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:47:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static size_t	len_next_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && !ft_iswhitespace(str[i]))
		i++;
	return (i);
}

void	parse_var(t_arg *arg, char **env)
{
	char	*var;
	char	*ptr;

	ptr = ft_strchr(arg->content, '$');
	if (ptr)
	{
		var = ft_strndup((const char *)ptr, len_next_whitespace(ptr));
		ptr = use_shell_var(env, var);
		ft_strdel(&arg->content);
		ft_strdel(&var);
		arg->content = ptr;
	}
}
