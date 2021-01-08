/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:11:30 by koala             #+#    #+#             */
/*   Updated: 2021/01/08 18:08:36 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
**	Heredoc parse line with "<<" substring to get EOF sequence
*/
void		here_doc(t_bash *data)
{
	t_arg	*lst;
	t_arg	*to_free;
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
						data->vector->doc_string = ft_strdup(ft_strchr(vect->line, vect->separator));
					if (data->vector->doc_string && ft_strstr(data->vector->doc_string, data->eof))
					{
						data->expend = 0;
						data->is_here_doc = 0;
						data->vector->separator = '<';
					}
				}
				if (ft_strstr(lst->content, "<<"))
				{
					to_free = lst;
					data->is_here_doc = 1;
				}
				lst = lst->next;
			}
		}
	}
	if (to_free)
	{
		to_free->previous->next = NULL;
		free_all_args(&to_free);
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
	char	*new_line;

	if (ft_strequ(LINE, data->eof) )
	{
		data->expend = 0;
		data->is_here_doc = 0;
		push_entry(data, "\n", &data->vector->line, data->iterator++);
		data->vector->up->doc_string = (data->vector->up->doc_string) ? str_join_free(&data->vector->up->doc_string, &LINE) : ft_strdup(LINE);
		ft_strdel(&data->eof);
		if (VECT_UP && data->vector->up->doc_string)
		{
			VECT = VECT_UP;
			free_vector(&data->vector->down);
		}
	}
	else
	{
		is_env_var(data);
		push_entry(data, "\n", &data->vector->line, data->iterator++);
		data->vector->up->doc_string = (data->vector->doc_string) ? str_join_free(&data->vector->up->doc_string, &LINE) : ft_strdup(LINE);
		ft_putchar('\n');
		if (VECT_UP && data->vector->up->doc_string)
			ft_strdel(&LINE);
	}
	data->y = 0;
	data->x = 0;
}

//void		handle_heredoc(t_bash *data, t_vect *command, char **args_array, char *path)
//{
//	int				pipe_fd[2];
//	int save;
//	int				status;
//	pid_t			cpid;
//	t_redirection	*new;
//
//	if (pipe(pipe_fd) < 0)
//		exit(1);
//	cpid = fork();
//	if (fork_failed(cpid))
//		print_failed_fork_error(cpid);
//	else if (is_child(cpid))
//	{
//		close(pipe_fd[1]);
//		new = new_redirection(command, 0);
//		new->left_fd = 0;
//		new->right_fd = pipe_fd[0];
//		if (command->redirections)
//			handle_redirections(data, command->redirections, 0);
//		if (!data->error)
//			execve(path, args_array, data->env);
//		exit(1);
//	}
//	else
//	{
//		close(pipe_fd[0]);
//		write(pipe_fd[1], command->doc_string, ft_strlen(command->doc_string));
//		close(pipe_fd[1]);
//		cpid = wait(NULL);
//	}
//}

void		handle_heredoc(t_bash *data, t_vect *command)
{
	int		pipe_fd[2];
	int		status;
	pid_t	cpid;

	if (pipe(pipe_fd) == EXIT)
		exit(EXIT);
	set_child_pipe_redirection(command, pipe_fd);
	pipe_fork(data, command, pipe_fd);
	write(pipe_fd[1], command->doc_string, ft_strlen(command->doc_string));
	close(pipe_fd[1]);
	wait(&status);
}