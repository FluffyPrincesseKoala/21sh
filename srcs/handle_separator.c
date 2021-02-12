/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:17:06 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 13:50:32 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

static t_arg	*handle_quote(t_bash *data, char **table,
						int i, int len, char quote)
{
	char		*string_with_quote;
	char		*quoted_string;
	t_arg		*ret;

	if ((string_with_quote = merge_string_from_array(table, len, i)))
	{
		if (quoted_string = unquote(string_with_quote, quote))
			if (add_arg(&VECT->args, (ret = new_arg(quoted_string, quote))))
				return (ret);
	}
	data->error = MALLOC_ERROR;
	return (NULL);
}

static void	handle_word(t_bash *data, char *str)
{
	if (!str || !VECT)
	{
		data->error = MALLOC_ERROR;
		return ;
	}
	add_arg(&VECT->args, new_arg(str, NOQUOTE));
}

void		words_as_args(char **table, t_bash *data)
{
	t_arg	*to_check;
	char	*tmp;
	char	*a;
	char	*b;
	int		len;
	int		i;

	i = 0;
	while (table[i] && !data->error)
	{
		a = ft_strchr(table[i], '\"'); //check if quote exist and keep there pointer in memory to handle them in order
		b = ft_strchr(table[i], '\'');
		if ((len = len_next_quote(table, i, '\"')) && ((a < b && a && b) || a && !b))
		{
			to_check = handle_quote(data, table, i, len, '\"');
			if (ft_strstr(to_check->content, "\\\""))
			{
				tmp = replace_substr(to_check->content, "\\\"", "\"");
				ft_strdel(&to_check->content);
				to_check->content = tmp;
			}
			if (ft_strstr(to_check->content, "\\\\"))
			{
				tmp = replace_substr(to_check->content, "\\\\", "\\");
				ft_strdel(&to_check->content);
				to_check->content = tmp;
			}
			get_var(&VECT->args, data->env);
			i += len;
		}
		else if ((len = len_next_quote(table, i, '\'')) && ((a > b && a && b) || b && !a))
		{
			handle_quote(data, table, i, len, '\'');
			i += len;
		}
		else
		{
			handle_word(data, ft_strdup(table[i]));
			get_var(&VECT->args, data->env);
			get_tilt(&VECT->args, data->env);
			i++;
		}
	}
}
