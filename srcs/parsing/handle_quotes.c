/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/12 15:09:56 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int  is_non_escaped_quote(const char *s, char quote, int i)
{
    if (s[i] != quote || (s[i] == quote && i && s[i - 1] == '\\')
			|| ((s[i] == quote && i > 1 && s[i - 1] == '\\' && s[i - 2] != '\\')))
        return (FALSE);
    else
        return (TRUE);
    
    //if (s[i] == quote && (i == 0 || (s[i - 1] != '\\' || (i > 1 && s[i - 2] == '\\'))))
    //    return (TRUE);
    //else
    //    return (FALSE);
}

static size_t	count_words(char const *s, char quote)
{
	size_t		i;
	size_t		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != quote || (s[i] == quote && i && s[i - 1] == '\\'))
		{
			words++;
			while (s[i] && !is_non_escaped_quote(s, quote, i))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static size_t	ft_strclen_noescape(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_non_escaped_quote(s, c, i))
		i++;
	return (i);
}

static char **split_quoted_string(char const *s, char c)
{
	char		**array;
	size_t		words;
	size_t		str_idx;
	size_t		array_idx;
	size_t		word_len;


	words = count_words(s, c);
	if (!(array = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	str_idx = 0;
	array_idx = 0;
	while (s[str_idx])
	{
		if (!is_non_escaped_quote(s, c, str_idx))
		{
			if (!(array[array_idx++] = ft_strndup(s + str_idx,
                (word_len = ft_strclen_noescape(s + str_idx, c)))))
				return (NULL);
			str_idx += word_len;
		}
		else
			str_idx++;
	}
	array[array_idx] = NULL;
	return (array);
}

char		*unquote(char *str, char delim)
{
	char	**tmp;
	char	*ret;
	int		i;
	int		j;
	int		p;

	i = 0;
	j = -1;
    tmp = split_quoted_string(str, delim);
	if (ret = malloc(sizeof(char) * (ft_arraylen_in_char(tmp) + 1)))
	{
		while (tmp[i])
		{
			p = -1;
			while (tmp[i][++p])
				ret[++j] = tmp[i][p];
			i++;
		}
		ret[++j] = '\0';
		free_array(tmp);
	}
	ft_strdel(&str);
	return (ret);
}