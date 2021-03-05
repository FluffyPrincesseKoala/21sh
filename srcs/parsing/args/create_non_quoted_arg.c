/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_non_quoted_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:42:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/05 18:47:55 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	get_tilt(t_arg *arg, char **env)
{
	char		*path_to_home;

	if (CONTENT && ft_strchr(CONTENT, '~'))
	{
		path_to_home = get_env_var_value(env, "HOME");
		CONTENT = ft_free_replaced_substr(CONTENT, "~", path_to_home);
	}
}

/*
** Search for redirection operator in given argument.
** Return a redirection setup structure that associate each redirection operator
**  with its set up function and file-opening flag.
*/

static void	parse_redirection_in_arg(t_bash *data, t_vect *cmd, t_arg *arg)
{
	int				i;
	char			*op;
	t_redirection	*new;

	i = 0;
	while (data->redirections_setup[i])
	{
		if (op = ft_strstr(arg->content, data->redirections_setup[i]->op))
		{
			if (!(op[0] == '<' && op[1] == '<'))
			{
				new = new_redirection(cmd);
				new->setup = data->redirections_setup[i];
				new->arg = arg;
				break ;
			}
		}
		i++;
	}
}

size_t		create_non_quoted_arg(t_bash *data, t_vect *cmd, char *line_extract)
{
	size_t	len;
	t_arg	*new_arg;

	len = 0;
	while (line_extract[len]
		&& !ft_iswhitespace(line_extract[len])
		&& !is_quote(line_extract[len])
		&& !is_separator(line_extract[len]))
		len++;
	if (!(new_arg = create_arg(ft_strsub(line_extract, 0, len))))
		data->error = MALLOC_ERROR;
	else
	{
		add_arg(&cmd->args, new_arg);
		parse_var(new_arg, data->env);
		get_tilt(new_arg, data->env);
		parse_redirection_in_arg(data, cmd, new_arg);
	}
	return (len);
}
