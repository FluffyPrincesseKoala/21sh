/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:02:05 by cylemair          #+#    #+#             */
/*   Updated: 2020/01/28 12:02:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strndup(const char *str, size_t size)
{
	char	*dup;

	if (!(dup = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strncpy(dup, str, size);
	dup[size] = '\0';
	return (dup);
}
