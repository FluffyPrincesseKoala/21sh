/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/02 17:32:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_arg   *create_arg(char *content)
{
    t_arg *new;
    
    if (new = ft_memalloc(sizeof(t_arg)))
    {
        if (new->content = content)
        {
            new->separator = contains_sperator(content);
            return (new);
        }
		else
		{
			new->content = NULL;
            new->separator = contains_sperator(content);
            return (new);
		}
    }
    ft_strdel(&content);
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

int    insert_new_arg(t_vect *command, t_arg *previous, char *s)
{
    t_arg *new;

    if (!(new = create_arg(s)))
        return (FAIL);
	if (previous)
	{
		new->next = previous->next;
    	new->previous = previous;
    	previous->next = new;
    	if (new->next)
    	    new->next->previous = new;
	    return (SUCCESS);
	}
    else
    {
        new->next = command->args;
        command->args->previous = new;
        command->args = new;
    }    
	return (-1);
}
