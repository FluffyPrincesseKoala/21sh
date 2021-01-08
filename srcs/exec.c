/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/08 11:06:41 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	free_two_var_to_feet_norm(char **a, char **b)
{
	ft_strdel(a);
	ft_strdel(b);
}
static size_t	ft_strclen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t		i;
	size_t		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

char		*fndup(const char *str, size_t size)
{
	char	*dup;
	size_t	i;

	i = 0;
	int lstr = ft_strlen(str);
	if (!(dup = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
char			**splity(char const *s, char c)
{
	size_t		words;
	char		**array;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(array = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(array[j++] = fndup(s + i, ft_strclen(s + i, c))))
				return (NULL);
			i += ft_strclen(s + i, c);
		}
		else
			i++;
	}
	array[j] = NULL;
	return (array);
}

char		*build_path(char **env, t_vect *lst)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**paths;
	int		ret;

	i = -1;
	tmp = NULL;
	tmp2 = NULL;
	paths = splity(findenv(env, "PATH"), ':');
	while (paths && paths[++i] && lst->args && lst->args->content)
	{
		tmp2 = ft_strjoin(paths[i], "/");
		tmp = (tmp2) ? ft_strjoin(tmp2, lst->args->content) : NULL;
		if (tmp && !(ret = access((const char*)tmp, F_OK)))
		{
			ft_strdel(&tmp2);
			free_array(paths);
			return (tmp);
		}
		free_two_var_to_feet_norm(&tmp, &tmp2);
	}
	free_two_var_to_feet_norm(&tmp, &tmp2);
	free_array(paths);
	return (NULL);
}
void		info(char *str)
{
	SAVE_C;
	GOTO(0, 0);
	printf("%s[%s]%s", RED, str, RESET);
	RESET_C;
}
static void print_failed_fork_error(pid_t pid)
{
	ft_putstr_fd("fork failed at ", 2);
	ft_putnbr_fd((int)pid, 2);
	ft_putchar('\n');
	exit(-1);
}

static char *choose_path(char *name, t_vect *cmd, t_bash *data)
{
	struct stat sb;
	char	*path;

	path = NULL;
	if (ft_strnequ(name, "./", 2) || (ft_strnequ(name, "../", 3))
		|| (ft_strnequ(name, "/", 1) && !access(name, X_OK)
			&& !access(name, F_OK) && !access(name, R_OK)))
		path = ft_strdup(name);
	else
		path = build_path(data->env, cmd);
	if (!path || (lstat(path, &sb) == 0 && S_ISDIR(sb.st_mode)))
	{
		put_error_msg(name);
		put_error_msg(UNOW);
		return (NULL);
	}
	return (path);
}
void lol(t_vect *command, char **args_array, char *path)
{
	SAVE_C;
	CDOWN;
	for (int i = 0 ; args_array[i] ; i++)
	{
		printf("%s[%s][%s]%s%s\n", RED, args_array[i], command->doc_string, path, RESET);
	}
	RESET_C;
}
void		handle_pipe(t_bash *data, t_vect *command)
{
	char			**args_array;
	char			*path;
	int				pipe_fd[2];
	pid_t			cpid;
    t_redirection   *new;

	pipe(pipe_fd);
	cpid = fork();
	if (fork_failed(cpid))
		print_failed_fork_error(cpid);
	else if (is_child(cpid))
	{
		close(pipe_fd[1]);
		command = command->next;
		args_array = arg_to_array(data, command->args);
		new = new_redirection(command, 0);
		new->left_fd = 0;
		new->right_fd = pipe_fd[0];
		if ((path = choose_path(*args_array, command, data)))
			execute_command(data, command, args_array, path);
		else
			exit(-1);
	}
	else
	{
		close(pipe_fd[0]);
		new = new_redirection(command, 0);
		new->left_fd = 1;
		new->right_fd = pipe_fd[1];
	}
}

void		handle_heredoc(t_bash *data, t_vect *command, char **args_array, char *path)
{
	int				pipe_fd[2];
	int save;
	int				status;
	pid_t			cpid;
	t_redirection	*new;

	if (pipe(pipe_fd) < 0)
		exit(1);
	cpid = fork();
	if (fork_failed(cpid))
		print_failed_fork_error(cpid);
	else if (is_child(cpid))
	{
		close(pipe_fd[1]);
		//dup2(pipe_fd[0], 0);
		new = new_redirection(command, 0);
		new->left_fd = 0;
		new->right_fd = pipe_fd[0];
		if (command->redirections)
			handle_redirections(data, command->redirections, 0);
		close(pipe_fd[0]);
		if (!data->error)
			execve(path, args_array, data->env);
		exit(1);
	}
	else
	{
		close(pipe_fd[0]);
		//dup2(1, save);
		//dup2(pipe_fd[1], 1);
		//close(pipe_fd[1]);
		write(pipe_fd[1], command->doc_string, ft_strlen(command->doc_string));
		close(pipe_fd[1]);
		//dup2(save, 1);
		cpid = wait(NULL);
	}
}

static void	execute_command(t_bash *data, t_vect *command, char **args_array, char *path)
{
	if (command->separator == '|')
	{
		handle_pipe(data, command);
	}
	if (command->doc_string)
	{
		handle_heredoc(data, command, args_array, path);
	}
	else
	{
		if (command->redirections)
			handle_redirections(data, command->redirections, 0);
		if (!data->error)
			execve(path, args_array, data->env);
	}
	exit(-1);
	//if (command->redirections)
	//	restore_directions(command->redirections);
}

void		handle_fork(t_bash *data, t_vect *command)
{
	char 	**args_array;
	char 	*path;
	int		status;
	pid_t	cpid;

	args_array = arg_to_array(data, command->args);
	if ((path = choose_path(*args_array, command, data)))
	{
		unconf_term();
		cpid = fork();
		if (fork_failed(cpid))
			print_failed_fork_error(cpid);
		else if (is_child(cpid))
			execute_command(data, command, args_array, path);
		wait(&status);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	}
	free_array(args_array);
	ft_strdel((path) ? &path : NULL);
	// fork();
	// int p[2];
	// pipe(p);
	// fork();
	// enfant: <p[0]
	// execute
	// parent: 1>p[1]
	// execute
}
