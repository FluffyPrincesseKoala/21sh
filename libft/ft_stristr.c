/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 18:20:37 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/19 16:37:54 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_stristr(const char *str, const char *to_find)
{
    int     i;
    int     j;

    i = 0;
    if (ft_strlen(to_find) == 0)
        return (0);
    while (str[i])
    {
        j = 0;
        while (str[i] == to_find[j])
        {
            if (to_find[j + 1] == '\0')
                return (i - j);
            i += 1;
            j += 1;
        }
    }
    return (-1);
}