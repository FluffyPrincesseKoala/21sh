/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_args_in_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:47:24 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:45:55 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static char	*get_content(t_arg *arg)
{
	if (arg->quoted)
		return (arg->quoted);
	return (arg->content);
}

static char	*concat_args_in_heredoc_line(t_arg *arg, char *concated_args)
{
	char	*str_with_space;
	char	*merged_string;

	merged_string = NULL;
	str_with_space = NULL;
	if (arg->content)
		if (concated_args)
			str_with_space = ft_strjoin(concated_args, " ");
	if (str_with_space)
		merged_string = ft_strjoin(str_with_space, get_content(arg));
	else if (concated_args)
		merged_string = ft_strjoin(concated_args, get_content(arg));
	else
		concated_args = ft_strdup(get_content(arg));
	ft_strdel(&str_with_space);
	if (merged_string)
		return (merged_string);
	return (concated_args);
}

char	*concat_args_in_heredoc(t_arg *arg)
{
	char	*concated_args;
	char	*merged_string;

	concated_args = NULL;
	merged_string = NULL;
	while (arg)
	{
		merged_string = concat_args_in_heredoc_line(arg, concated_args);
		if (concated_args && merged_string)
			ft_strdel(&concated_args);
		concated_args = merged_string;
		arg = arg->next;
	}
	return (concated_args);
}
