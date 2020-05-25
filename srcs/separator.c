/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:17:06 by cylemair          #+#    #+#             */
/*   Updated: 2020/05/09 16:45:17 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_vect		*new_arg(t_lst *args, t_vect *new)
{
	if (new->args)
		new = vect_add(&new, vect_new(args, NULL));
	else if (new)
		new->args = args;
	return (new);
}

// quote
int			next_simple_quote(char **array, int start)
{
	int		count;
	int		len;
	char	*a;
	char	*b;

	len = 0;
	count = 0;
	if (ft_strchr(array[start], '\''))
	{
		count = 1;
		if ((a = ft_strchr(array[start + len], '\''))
			&& (b = ft_strrchr(array[start + len], '\'')) && a != b)
			return (1);
		else
		{		
			while (array && array[start + ++len]
			&& count)
			{
				if (ft_strchr(array[start + len], '\''))
					count--;
			}
		}
	}
	return (len);
}

int			next_double_quote(char **array, int start)
{
	int		count;
	int		len;
	char	*a;
	char	*b;

	len = 0;
	count = 0;
	if (ft_strchr(array[start], '\"'))
	{
		count = 1;
		if ((a = ft_strchr(array[start + len], '\"'))
			&& (b = ft_strrchr(array[start + len], '\"')) && a != b)
			return (1);
		else
		{		
			while (array && array[start + ++len]
			&& count)
			{
				if (ft_strchr(array[start + len], '\"'))
					count--;
			}
		}
	}
	return (len);
}

int			next_delim(char **array, int start)
{
	int		len;

	len = 0;
	while (array && array[start + len]
		&& array[start + len][0] != '|' && array[start + len][0] != ';'
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
	if (!(ret = malloc(sizeof(char) * (array_total_len(tmp) + 1))))
		return (NULL);
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
	return (ret);
}

t_vect		*read_separator(char **table, t_bash *data)
{
	t_lst	*args;
	char	*tmp;
	char	*final;
	char	**new_tab;
	t_vect	*new;
	int		len;
	int		i;

	i = 0;
	new = vect_new(NULL, LINE);
	new_tab = NULL;
	final = NULL;
	while (table[i] && !data->error)
	{
		len = 0;
		if ((len = next_simple_quote(table, i)))
		{
			if ((tmp = merge_string_from_array(table, len, i)))
			{
				// if  i = \ && i + 1 = quote => not del on '' || del on ""
				//if \" do variable convertion; else nope
				if ((final = del_all_delim_in(tmp, '\'')))
				{
					lstadd(&new->args, lstnew(final));
					i += len;
				}
				ft_strdel(&tmp);
				ft_strdel(&final);
			}
			else
			{
				ft_strdel(&data->error);
				data->error = ft_strdup(HOOK_MALLOC);
			}
		}
		else if ((len = next_double_quote(table, i)))
		{
			if ((tmp = merge_string_from_array(table, len, i)))
			{
				if ((final = del_all_delim_in(tmp, '\"')))
				{
					lstadd(&new->args, lstnew(final));
					get_var(&new->args, data->env),
					i += len;
				}
				ft_strdel(&tmp);
				ft_strdel(&final);
			}
			else
			{
				ft_strdel(&data->error);
				data->error = ft_strdup(HOOK_MALLOC);
			}
		}
		else if ((len = next_delim(table, i)))
		{
			args = pop_lst_from_array(table, len, i);;
			new = new_arg(args, new);
			get_var(&new->args, data->env),
			i += len;
		}
		else if (((table[i+len][0] == '|') || (table[i + len][0] == ';')) && !i)
		{
			ft_strdel(&data->error);
			data->error = ft_strjoin(SYNTAX, table[i + len]);
		}
		else
			i++;
	}
	return (new);
}

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

t_vect		*format_line(t_bash *data)
{
	t_vect	*new;
	char	*tmp;
	char	**table;

	new = NULL;
	tmp = NULL;
	table = NULL;

	if (LINE)
		tmp = space_separator(LINE);
	if (tmp)
	{
		if (array_len(table = ft_strsplit(tmp, ' ')))
		{
			new = read_separator(table, data);
			free_array(table);
			new->up = data->vector->up;
			new->down = data->vector->down;
			if (data->vector)
				free_vector(&data->vector);
			data->vector = new;
		}
	}
	data->vector = link_history(&data->vector, vect_new(NULL, NULL));
	ft_strdel(&tmp);
	return (data->vector);
}