/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/22 19:23:16 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**copy_array(char **array)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	while (array[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int			array_total_len(char **array)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	return (len);
}

void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		ft_strdel(&array[i]);
		array[i] = NULL;
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

void		print_array(char **array)
{
	int i;

	i = 0;
	ft_putchar('\n');
	while (array && array[i])
	{
		ft_putstr(array[i]);
		ft_putchar('\n');
		i++;
	}
}

static size_t	ft_strclen_noescape(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c || (s[i] == c && i && s[i - 1] == '\\') 
			|| ((s[i] == c && i > 1 && s[i - 1] == '\\' && s[i - 2] != '\\'))))
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
		if (s[i] != c || (s[i] == c && i && s[i - 1] == '\\'))
		{
			words++;
			while (s[i] && (s[i] != c || (s[i] == c && i && s[i - 1] == '\\')
				|| ((s[i] == c && i > 1 && s[i - 1] == '\\' && s[i - 2] != '\\'))))
				i++;
		}
		else
			i++;
	}
	return (words);
}

char			**fsplit(char const *s, char c)
{
	char		**tabatata;
	size_t		words;
	size_t		i;
	size_t		j;
	size_t		pute;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(tabatata = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c || (s[i] == c && i && s[i - 1] == '\\')
			|| ((s[i] == c && i > 1 && s[i - 1] == '\\' && s[i - 2] != '\\')))
		{
			if (!(tabatata[j++] = ft_strndup(s + i, (pute = ft_strclen_noescape(s + i, c)))))
				return (NULL);
			i += pute;
		}
		else
			i++;
	}
	tabatata[j] = NULL;
	return (tabatata);
}

char		*del_all_delim_in(char *str, char delim)
{
	char	**tmp;
	char	*ret;
	int		i;
	int		j;
	int		p;

	i = 0;
	j = -1;
	tmp = fsplit(str, delim);
	if (ret = malloc(sizeof(char) * (array_total_len(tmp) + 1)))
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
