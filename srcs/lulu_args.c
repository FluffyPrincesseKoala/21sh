/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:06:51 by cylemair          #+#    #+#             */
/*   Updated: 2020/04/24 22:13:59 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 21sh.h

t_arg   *new_arg(char *s)
{
    t_arg *new;

    if (!new = memalloc(sizeof(t_arg)))
        return (NULL);
    new->s = ft_strdup(s);
    return (new);
}

void    detach_arg(t_arg *arg)
{
    if (arg->previous)
        arg->previous->next = arg->next;
    if (arg->next)
        arg->next->previous = arg->previous;
}

void del_arg(t_arg *arg)
{
    detach_arg(arg);
    ft_strdel(arg->s);
    free(arg);
    arg = NULL;
}

int    insert_new_arg(t_arg *previous, char *s)
{
    t_arg *new;

    if (!new = new_arg(s))
        return (0);
    new->next = previous->next;
    new->previous = previous;
    previous->next = new;
    if (new->next)
        new->next->previous = new;
    return (1);
}
