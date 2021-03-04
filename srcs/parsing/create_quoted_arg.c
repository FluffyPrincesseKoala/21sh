/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:41:08 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 17:38:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	handle_double_quote(t_bash *data, t_vect *cmd, t_arg *arg)
{
	if (ft_strstr(arg->content, "\\\""))
		arg->content = ft_free_replaced_substr(arg->content, "\\\"", "\"");
	if (ft_strstr(arg->content, "\\\\"))
		arg->content = ft_free_replaced_substr(arg->content, "\\\\", "\\");
	get_var(cmd->args, data->env);
}

size_t	    create_quoted_arg(t_bash *data, t_vect *cmd, char *line_substr, char quote)
{
	char	*unquoted_str;
	t_arg	*new_arg;
	size_t	len;

	if (unquoted_str = unquote(line_substr, quote))
	{
		len = ft_strlen(unquoted_str) + 2;
		if (new_arg = create_arg(unquoted_str))
		{
			add_arg(&cmd->args, new_arg);
			if (quote == '\"')
				handle_double_quote(data, cmd, new_arg);
			return (len);
		}
	}
	data->error = MALLOC_ERROR;
	return (0);
}