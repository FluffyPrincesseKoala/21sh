/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 20:10:47 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/15 18:18:21 by cylemair         ###   ########.fr       */
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
void		print_failed_fork_error(pid_t pid)
{
	ft_putstr_fd("fork failed at ", 2);
	ft_putnbr_fd((int)pid, 2);
	ft_putchar('\n');
	exit(-1);
}

char		*choose_path(char *name, t_vect *cmd, t_bash *data)
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
		printf("%s[%s][%s]%s%s\n", RED, args_array[i], *(command->doc_string), path, RESET);
	}
	RESET_C;
}
