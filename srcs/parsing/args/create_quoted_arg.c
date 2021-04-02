/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:41:08 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:49:48 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static size_t	len_until_non_escaped_quote(char *s, char quote)
{
	size_t	len;

	len = 1;
	while (s[len] && !is_non_escaped_quote(s, quote, len))
		len++;
	return (len);
}

static char	*unquote(char *line_substr, char quote)
{
	size_t	len;

	len = len_until_non_escaped_quote(line_substr, quote);
	return (ft_strsub(line_substr, 1, len - 1));
}

static char	*extract_quoted_str(char *line_substr, char quote)
{
	size_t	len;

	len = len_until_non_escaped_quote(line_substr, quote);
	return (ft_strsub(line_substr, 0, len + 1));
}

static void	handle_double_quote(t_bash *data, t_arg *arg)
{
	if (ft_strstr(arg->content, "\\\""))
	{
		arg->content = ft_free_replaced_substr(arg->content, "\\\"", "\"");
		if (!(arg->content))
			data->error = MALLOC_ERROR;
	}
	if (ft_strstr(arg->content, "\\\\"))
	{
		arg->content = ft_free_replaced_substr(arg->content, "\\\\", "\\");
		if (!(arg->content))
			data->error = MALLOC_ERROR;
	}
	parse_var(arg, data->env);
}

size_t	create_quoted_arg(
	t_bash *data, t_vect *cmd, char *line_substr, char quote)
{
	char	*unquoted_str;
	char	*quoted_str;
	t_arg	*new_arg;

	unquoted_str = unquote(line_substr, quote);
	if (unquoted_str)
	{
		quoted_str = extract_quoted_str(line_substr, quote);
		new_arg = create_arg(unquoted_str, quoted_str);
		if (new_arg)
		{
			add_arg(&cmd->args, new_arg);
			if (quote == '\"')
				handle_double_quote(data, new_arg);
			return (len_until_non_escaped_quote(line_substr, quote) + 1);
		}
	}
	data->error = MALLOC_ERROR;
	return (0);
}
