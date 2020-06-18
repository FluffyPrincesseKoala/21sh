/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:17:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/03 19:20:29 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void set_arg_to_vect(t_bash *data, t_lst *args)
{
	if (VECT->args)
		vect_add(&VECT, vect_new(args, NULL));
	else if (VECT)
		VECT->args = args;
}

int			len_next_quote(char **array, int start, int quote)
{
	int		count;
	int		len;
	char	*a;
	char	*b;

	len = 0;
	count = 0;
	if (ft_strchr(array[start], quote))
	{
		count = 1;
		if ((a = ft_strchr(array[start + len], quote))
			&& ((b = ft_strrchr(array[start + len], quote)) && a != b))
			return (1);
		else
		{		
			while (array && array[start + ++len]
			&& count)
			{
				if (ft_strchr(array[start + len], quote))
					count--;
			}
		}
	}
	return (len);
}

int			len_before_next_delim(char **array, int start)
{
	int		len;

	len = 0;
	while (array && array[start + len]
		&& array[start + len][0] != '|' && array[start + len][0] != ';' && array[start + len][0] != '\n'
		&& array[start + len][0] != '\'' && array[start + len][0] != '\"')
		len++;
	return (len);
}

char		**replace_subarray_by_string(char **array, char *str, int size, int start)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char*) * (array_len(array) - size + 2))))
		return (NULL);
	while (array[i])
	{
		if (i == start)
		{
			new[j] = ft_strdup(str);
			i += size;
		}
		else
		{		
			new[j] = ft_strdup(array[i]);
			i++;
		}
		j++;
	}
	new[j] = NULL;
	return (new);
}

char		*del_all_delim_in(char *str, char delim)
{
	char	**tmp;
	char	*ret;
	int		i;
	int		j;
	int		p;

	i = 0;
	j = 0;
	tmp = ft_strsplit(str, delim);
	if (ret = malloc(sizeof(char) * (array_total_len(tmp) + 1)))
	{
		while (tmp[i])
		{
			p = 0;
			while (tmp[i][p])
			{
				ret[j] = tmp[i][p];
				p++;
				j++;
			}
			i++;
		}
		ret[j] = '\0';
		free_array(tmp);
	}
	ft_strdel(&str);
	return (ret);
}

static void	handle_quote(t_bash *data, char **table, int i, int len, char quote)
{
	char	*string_with_quote;
	char	*quoted_string;

	if ((string_with_quote = merge_string_from_array(table, len, i)))
	{
		if (!(quoted_string = del_all_delim_in(string_with_quote, quote)))
		{
			ft_strdel(&data->error); // remove when static table
			data->error = ft_strdup(HOOK_MALLOC);
			return ;
		}
		lstadd(&VECT->args, lstnew(quoted_string, quote));
		ft_strdel(&quoted_string);
	}
	else
	{
		ft_strdel(&data->error); // remove when static table
		data->error = ft_strdup(HOOK_MALLOC);
	}
}

static void	handle_word(t_bash *data, char *str)
{
	if (!str || !VECT)
	{
		ft_strdel(&data->error);
		data->error = ft_strdup(HOOK_MALLOC);
		return ;
	}
	lstadd(&VECT->args, lstnew(str, NOQUOTE));
}

void		words_as_args(char **table, t_bash *data)
{
	t_lst	*args;
	int		len;
	int		i;

	i = 0;
	while (table[i] && !data->error)
	{
		if ((len = len_next_quote(table, i, '\'')))
		{
			handle_quote(data, table, i, len, '\'');
			i += len;
		}
		else if ((len = len_next_quote(table, i, '\"')))
		{
			handle_quote(data, table, i, len, '\"');
			get_var(&VECT->args, data->env);
			i += len;
		}
		else
		{
			handle_word(data, table[i]);
			i++;
		}
	}
}

/*
** récupérer les quote, créer args au fur et à mesure
** avoir une variable dans t_lst, qui indique si quote ou pas
** reparser pour les separateur en ignorant les args qui sont des quote
*/
 
static char	*space_separator(char *line)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	if (line)
	{
		tmp = replace_substr(line, ";", " ; ");
		ret = replace_substr((tmp) ? tmp : line, "|", " | ");
		ft_strdel(&tmp);
	}
	return (ret);
}

static int	contains_sperator(char *str)
{
	int		i;
	int		j;
	char	*separator;

	i = 0;
	separator = ";\n|";
	while (str && str[i])
	{
		j = 0;
		while (separator[j])
		{
			if (str[i] == separator[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void		detach_args(t_vect *current, t_lst *last_arg_before_doomsday)
{
	if (last_arg_before_doomsday->next)
	{
		current->next = vect_new(last_arg_before_doomsday->next, NULL);
		last_arg_before_doomsday->next = NULL;
	}
}

void		get_post_separator_args(t_bash *data, t_lst *lst, int index, int len)
{
	char	*sub_string;
	t_lst	*new_arg;

	sub_string = NULL;
	new_arg = NULL;
	if (sub_string = ft_strsub(lst->content, index, len - index))
	{
		if ((new_arg = lstnew(sub_string, 0)))
		{
			lst_add_after(lst, new_arg);
			return ;
		}
		ft_strdel(&sub_string);
	}
	ft_strdel(&data->error);
	data->error = ft_strdup(HOOK_MALLOC);
}

void		parse_args(t_bash *data, t_vect *current)
{
	t_lst	*lst;
	unsigned int	i;
	unsigned int	len;
	unsigned int	separator_idx;

	i = 0;
	len = 0;
	separator_idx = 0;
	if (current->args)
		lst = current->args;
	while (lst)
	{
		if ((separator_idx = contains_sperator(lst->content)) != -1
		&& !lst->quote)
		{
			current->separator = lst->content[separator_idx];
			if ((len = ft_strlen(lst->content)) != separator_idx + 1)
				get_post_separator_args(data, lst, separator_idx + 1, len);
			detach_args(current, lst);
			lst->content = ft_strsub_free(&lst->content, 0, separator_idx);
		}
		lst = lst->next;
	}
}

void		format_line(t_bash *data)
{
	t_vect	*loop;
	char	**table;

	if (array_len(table = ft_strsplit(LINE, ' ')))
	{
		words_as_args(table, data);
		free_array(table);
	}
	if (VECT->args && !data->error)
	{
		loop = VECT;
		while (loop)
		{
			parse_args(data, loop);
			loop = loop->next;
		}
	}
	else
		puterror(data->error);
}