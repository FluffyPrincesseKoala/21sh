/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:41:08 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 11:04:16 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	is_non_escaped_quote(const char *s, char quote, int i)
{
	if (s[i] == quote
		&& (i == 0 || (s[i - 1] != '\\' || (i > 1 && s[i - 2] == '\\'))))
		return (TRUE);
	else
		return (FALSE);
}

static char	*unquote(char *line_substr, char quote)
{
	size_t	len;

	len = 1;
	while (line_substr[len] && !is_non_escaped_quote(line_substr, quote, len))
		len++;
	return (ft_strsub(line_substr, 1, len - 1));
}

static void	handle_double_quote(t_bash *data, t_arg *arg)
{
	if (ft_strstr(arg->content, "\\\""))
		if (!(arg->content = ft_free_replaced_substr(arg->content,
			"\\\"", "\"")))
			data->error = MALLOC_ERROR;
	if (ft_strstr(arg->content, "\\\\"))
		if (!(arg->content = ft_free_replaced_substr(arg->content,
			"\\\\", "\\")))
			data->error = MALLOC_ERROR;
	parse_var(arg, data->env);
}

size_t		create_quoted_arg(
	t_bash *data, t_vect *cmd, char *line_substr, char quote)
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
				handle_double_quote(data, new_arg);
			return (len);
		}
	}
	data->error = MALLOC_ERROR;
	return (0);
}
