/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2020/12/22 17:12:29 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		here_doc(t_bash *data)
{
	t_arg	*lst;
	t_vect	*vect;

	data->is_here_doc = 0;
	if ((vect = data->vector))
	{
		if ((lst = vect->args))
		{
			while (lst)
			{
				if (data->is_here_doc == 1)
				{
					data->eof = ft_strdup(lst->content);
					if (vect->separator)
						data->doc_string = ft_strdup(ft_strchr(vect->line, vect->separator));
					if (data->doc_string && ft_strstr(data->doc_string, data->eof))
					{
						data->expend = 0;
						data->is_here_doc = 0;
						//do redirection stuff
						ft_putendl(BLUE);
						ft_putstr(data->doc_string);
						ft_putstr(RESET);
						ft_strdel(&data->doc_string);
					}
				}
				if (ft_strstr(lst->content, "<<"))
					data->is_here_doc = 1;
				lst = lst->next;
			}
		}
	}
	data->expend = (data->is_here_doc) ? -1 : data->expend;
}

void	is_env_var(t_bash *data)
{
	char	*ret;
	char	*tmp;
	char	*potential_shell_var;
	char	*shell_var;
	size_t	len_var;
	size_t	len_space;

	ret = NULL;
	tmp = NULL;
	potential_shell_var = NULL;
	len_var = 0;
	len_space = 0;
	if ((potential_shell_var = ft_strchr(LINE, '$')))
	{
		len_var = lendelim(potential_shell_var, '$', 0);
		len_space = lendelim(potential_shell_var, ' ', 0);
		shell_var = ft_strndup(potential_shell_var,
			(len_space < len_var) ? len_space : len_var);
		if (!ft_strequ(tmp = use_shell_var(data->env, shell_var), ""))
		{
			ret = replace_substr(LINE, shell_var, tmp);
			ft_strdel(&LINE);
			LINE = ft_strdup(ret);
			ft_strdel(&ret);
		}
		ft_strdel(&shell_var);
		ft_strdel(&tmp);
	}
}

int			 update_heredoc(t_bash *data)
{
	char	*tmp;

	if (ft_strequ(LINE, data->eof))
	{
		data->expend = 0;
		data->is_here_doc = 0;
		push_entry(data, "\n", &data->vector->line, data->iterator++);
		data->doc_string = (data->doc_string) ? str_join_free(&data->doc_string, &LINE) : ft_strdup(LINE);
		ft_strdel(&data->eof);
		//do redirection stuff
		ft_putendl(BLUE);
		ft_putstr(data->doc_string);
		ft_putstr(RESET);
		if (VECT_UP)
		{
			tmp = ft_strjoin("\n", data->doc_string);
			VECT_UP->line = str_join_free(&VECT_UP->line, &tmp);
		}
		ft_strdel(&data->doc_string);
	}
	else
	{
		is_env_var(data);
		push_entry(data, "\n", &data->vector->line, data->iterator++);
		data->doc_string = (data->doc_string) ? str_join_free(&data->doc_string, &LINE) : ft_strdup(LINE);
		ft_putchar('\n');
	}
	ft_strdel(&LINE);
	data->y = 0;
	data->x = 0;
}
