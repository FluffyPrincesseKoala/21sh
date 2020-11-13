/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/10 12:30:51 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_arg   *new_arg(char *content, char quote)
{
    t_arg *new;
    
    if (new = ft_memalloc(sizeof(t_arg)))
    {
        if (new->content = ft_strsub_free(&content, 0, ft_strlen(content)))
        {
            new->quote = quote;
            return (new);
        }
    }
    ft_strdel(&content);
    free(new);
    return (NULL);
}

t_arg   *add_arg(t_arg **head, t_arg *new)
{
    t_arg *cursor;

    if (!*head)
        *head = new;
    else
    {
        cursor = *head;
        while (cursor->next)
            cursor = cursor->next;
        cursor->next = new;
        new->previous = cursor;
    }
}

int    insert_new_arg(t_arg *previous, char *s)
{
    t_arg *new;

    if (!(new = new_arg(s, NOQUOTE)))
        return (0);
    new->next = previous->next;
    new->previous = previous;
    previous->next = new;
    if (new->next)
        new->next->previous = new;
    return (1);
}

void    detach_arg(t_arg *arg, t_vect *cmd)
{
    if (cmd->args == arg)
        cmd->args = arg->next;
    if (arg->previous)
        arg->previous->next = arg->next;
    if (arg->next)
        arg->next->previous = arg->previous;
}

void del_one_arg(t_arg *arg, t_vect *cmd)
{
    detach_arg(arg, cmd);
    ft_strdel(&CONTENT);
    free(arg);
    arg = NULL;
}

size_t  args_len(t_arg *arg)
{
    size_t len;

    len = 0;
    while (arg)
    {
        if (CONTENT)
            len++;
        arg = arg->next;
    }
    return len;
}

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