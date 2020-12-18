/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/18 17:03:04 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char    **arg_to_array(t_bash *data, t_arg *arg)
{
    char    **array;
    int     i;

    if (!(array = malloc(sizeof(char*) * (args_len(arg) + 1))))
        data->error = MALLOC_ERROR;
    else
    {
        i = 0;
        while (arg)
        {
            if (CONTENT)
            {
                array[i] = ft_strdup(CONTENT);
                i++;
            }
            arg = arg->next;
        }
        array[i] = NULL;
    }
    return (array);
}

void    free_all_args(t_arg *arg)
{
    if (arg)
    {
        ft_strdel(&CONTENT);
        free_all_args(arg->next);
        arg->previous = NULL;
        arg->next = NULL;
        free(arg);
    }
}

void del_one_arg(t_arg *arg, t_vect *cmd)
{
    detach_arg(arg, cmd);
    ft_strdel(&CONTENT);
    free(arg);
    arg = NULL;
}