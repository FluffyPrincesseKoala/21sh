/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/04 22:59:13 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int     search_in_fd(t_bash *data, t_arg *arg, int operator_index, int default)
{
    char *substring;

    if (operator_index > 0)
    {
        if (!substring = ft_strsub(arg->s, 0, operator_index))
                data->error = "error malloc";
        else if (ft_str_is_digits(substring))
            return ft_atoi(substring);
        else
            if (!insert_new_arg(arg->previous, substring))
                data->error = "error malloc";
        ft_strdel(substring);
    }
    return default;
}

int     search_out_fd(t_bash *data, char *substring)
{
    if (substring[0] == '&')
    {
        if (ft_str_is_digits(&(substring[1])))
            return ft_atoi(&(substring[1]))
        else
        {
            data->error = "error redirection ambigue"
            return (-1)
        }
    }
    return (0)
}

char    *search_out_file(t_bash *data, t_arg *arg, int substring_index)
{
    char *file;

    file = NULL;
    if (substring_index != ft_strlen(arg->s))
        if (!file = ft_strsub(arg->s, substring_index, ft_strlen(arg->s)))
            data->error = "error malloc"
    else if (arg->next)
    {
        if(!file = ft_strdup(arg->next->s))
            data->error = "error malloc";
        del_arg(arg->next)
    }
    else
        data->error = "error fin de commande innatendue"
    return file;
}
