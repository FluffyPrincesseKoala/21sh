/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2021/01/15 18:22:58 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	unlink_free_vector(t_vect **head)
{
	t_vect	*lst;
	t_vect	*nxt_lst;
	t_arg	*nxt_arg;

	if (head && (lst = *head))
	{
		while (lst)
		{
			nxt_lst = lst->next;
			ft_strdel(&lst->line);
			while (lst->args)
			{
				nxt_arg = lst->args->next;
				ft_strdel(&lst->args->content);
				lst->args->content = NULL;
				lst->args->previous = NULL;
				free(lst->args);
				lst->args = NULL;
				lst->args = nxt_arg;
			}
			free(lst);
			lst = NULL;
			lst = nxt_lst;
		}
		*head = NULL;
		head = NULL;
	}
}

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/
void		here_doc(t_bash *data)
{
	t_arg	*lst;
	t_arg	*to_free;
	t_vect	*vect;
	t_vect	*vect_to_free;

	data->is_here_doc = 0;
	to_free = NULL;
	vect_to_free = NULL;
	if ((vect = data->vector))
	{
		if ((lst = vect->args)) // do a while ?
		{
			while (lst && lst->content)
			{
				if (data->is_here_doc == 1)
				{
					if (!(data->eof = ft_strdup(lst->content)))
					{
						put_error_msg(SYNTAX);
						put_error_msg("new line\n");
					}
					if (vect->separator == '\n' && (vect_to_free = vect))
					{
						vect->separator = 0;
						while ((vect = vect->next))
						{
							if (VECT->doc_string)
								VECT->doc_string = array_add_value(VECT->doc_string, vect->args->content);
							else
								VECT->doc_string = create_array(vect->args->content);
						}
						data->is_here_doc = 0;
						data->expend = 0;
						unlink_free_vector(&vect_to_free->next);
						vect_to_free->next = NULL;
					}
				}
				if (lst->content && ft_strstr(lst->content, "<<"))
				{
					to_free = lst;
					data->is_here_doc = 1;
				}
				lst = lst->next;
			}
		}
	}
	if (to_free) // move this up
	{
		to_free->previous->next = NULL;
		free_all_args(&to_free, FALSE);
	}
	data->expend = (data->is_here_doc) ? -1 : data->expend;
}

void		is_env_var(t_bash *data)
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

int			update_heredoc(t_bash *data)
{
	char	**tmp;
	char	*str;

	if (ft_strequ(LINE, data->eof))
	{
		data->expend = 0;
		data->is_here_doc = 0;
		str = ft_strjoin(VECT_UP->line, "\n");
		ft_strdel(&VECT_UP->line);
		VECT_UP->line = ft_strjoin(str, LINE);
		ft_strdel(&LINE);
		ft_strdel(&str);
		if (VECT_UP && VECT_UP->doc_string)
		{
			VECT = VECT_UP;
			free_vector(&data->vector->down, FALSE);
		}
	}
	else
	{
		is_env_var(data);
		if (VECT_UP->doc_string)
		{
			VECT_UP->doc_string = array_add_value(VECT_UP->doc_string, LINE);
		}
		else
		{
			VECT_UP->doc_string = create_array(LINE);
		}
		ft_putchar('\n');
		if (VECT_UP && VECT_UP->doc_string)
		{
		 	str = ft_strjoin(VECT_UP->line, "\n");
		 	ft_strdel(&VECT_UP->line);
		 	VECT_UP->line = ft_strjoin(str, LINE);
		 	ft_strdel(&LINE);
		 	ft_strdel(&str);
		}
	}
	data->y = 0;
	data->x = 0;
}

void		write_heredoc(t_bash *data, t_vect *command, int pipe_fd[2])
{
	int i;

	i=0;
	while ((command->doc_string)[i])
	{
		write(pipe_fd[1], (command->doc_string)[i], ft_strlen((command->doc_string)[i]));
		write(pipe_fd[1], "\n", 1);
		i++;
	}

}

void		handle_heredoc(t_bash *data, t_vect *command)
{
	int		i;
	int		pipe_fd[2];
	int		status;
	pid_t	cpid;


    if (using_heredoc(command))
	{
		if (pipe(pipe_fd) == EXIT)
			exit(EXIT);
		set_child_pipe_redirection(command, pipe_fd);
		pipe_fork(data, command, pipe_fd, TRUE);
	}
}