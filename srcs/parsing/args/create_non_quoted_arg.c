/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_non_quoted_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:42:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:50:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	get_tilt(t_arg *arg, char **env)
{
	char		*path_to_home;

	if (arg->content && ft_strchr(arg->content, '~'))
	{
		path_to_home = get_value_from_env(env, "HOME");
		arg->content = ft_free_replaced_substr(arg->content, "~", path_to_home);
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
	while (data->redirect_setup[i])
	{
		op = ft_strstr(arg->content, data->redirect_setup[i]->op);
		if (op)
		{
			if (!(op[0] == '<' && op[1] == '<'))
			{
				new = new_redirection(cmd, FALSE);
				new->setup = data->redirect_setup[i];
				new->arg = arg;
				break ;
			}
		}
		i++;
	}
}

size_t	create_non_quoted_arg(t_bash *data, t_vect *cmd, char *line_extract)
{
	size_t	len;
	t_arg	*new_arg;

	len = 0;
	while (line_extract[len]
		&& !ft_iswhitespace(line_extract[len])
		&& !is_quote(line_extract[len])
		&& !is_separator(line_extract[len]))
		len++;
	new_arg = create_arg(ft_strsub(line_extract, 0, len), NULL);
	if (!new_arg)
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
