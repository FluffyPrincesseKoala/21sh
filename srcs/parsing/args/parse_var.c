/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:53:23 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/09 12:31:33 by koala            ###   ########.fr       */
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

void			parse_var(t_arg *arg, char **env)
{
	char	*var;
	char	*ptr;

	if (arg->content && (ptr = ft_strchr(arg->content, '$')))
	{
		var = ft_strndup((const char *)ptr, len_next_whitespace(ptr));
		ptr = use_shell_var(env, var);
		ft_strdel(&arg->content);
		ft_strdel(&var);
		arg->content = ptr;
	}
}
