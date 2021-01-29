/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/29 11:33:56 by cylemair         ###   ########.fr       */
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
		else
		{
			new->content = ft_strdup("");
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

int    insert_new_arg(t_vect *command, t_arg *previous, char *s)
{
    t_arg *new;

    if (!(new = new_arg(s, NOQUOTE)))
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

void    detach_arg(t_arg *arg, t_vect *cmd)
{
    if (cmd->args == arg)
        cmd->args = arg->next;
    if (arg->previous)
        arg->previous->next = arg->next;
    if (arg->next)
        arg->next->previous = arg->previous;
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
