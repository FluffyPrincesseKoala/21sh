/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_digits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 12:46:15 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/27 09:16:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** These functions check whether s, is a string that contains digits only. 
** The values return are 0 if s is null or s does not match the condition,
** 1 eitherway.
*/

int ft_str_is_digits(const char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}