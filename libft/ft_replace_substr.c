/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_substr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:34:05 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:37:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	new_len(char *str, char *old, char *new)
{
	size_t		i;
	size_t		j;
	size_t		len_ret;

	i = 0;
	len_ret = 0;
	while (str[i])
	{
		if (!ft_strncmp((str + i), old, ft_strlen(old)))
		{
			j = 0;
			while (old[j] && str[i + j])
				j++;
			len_ret += (j == ft_strlen(old)) ? ft_strlen(new) + 1 : 1;
			i += ft_strlen(old);
		}
		else
		{
			len_ret++;
			i++;
		}
	}
	return (len_ret);
}

char			*ft_replace_substr(char *str, char *old, char *new)
{
	char		*ret;
	int			i;
	int			j;
	int			k;
	size_t		len_old;

	len_old = ft_strlen(old);
	if (!(ret = malloc(sizeof(char) * (new_len(str, old, new) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strncmp((str + i), old, len_old))
		{
			k = 0;
			while (new[k])
				ret[j++] = new[k++];
			i += len_old;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
}

char			*ft_free_replaced_substr(char *str, char *old, char *new)
{
	char *result;

	if (!new)
	{
		new = ft_strdup("");
		result = ft_replace_substr(str, old, new);
		ft_strdel(&new);
	}
	else
		result = ft_replace_substr(str, old, new);
	ft_strdel(&str);
	return (result);
}
