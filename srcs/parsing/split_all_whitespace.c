/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_all_whitespace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:57:54 by koala             #+#    #+#             */
/*   Updated: 2021/01/19 15:03:31 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static size_t	strclen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_iswhitespace(str[i]))
		i++;
	return (i);
}

static size_t	count_words(char const *s)
{
	size_t		i;
	size_t		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]))
		{
			words++;
			while (s[i] && !ft_iswhitespace(s[i]))
				i++;
		}
		else
			i++;
	}
	return (words);
}

char			**split_all_whitespace(char const *s)
{
	size_t		words;
	char		**array;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	words = count_words(s);
	if (!(array = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]))
		{
			if (!(array[j++] = ft_strndup(s + i, strclen(s + i))))
				return (NULL);
			i += strclen(s + i);
		}
		else
			i++;
	}
	array[j] = NULL;
	return (array);
}
