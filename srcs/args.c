/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:04 by cylemair          #+#    #+#             */
/*   Updated: 2021/02/05 18:26:37 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		print_args(t_bash *data, t_vect *command)
{
	t_arg	*arg;

	if (command->args)
		arg = command->args->next;
	while (arg)
	{
		ft_putstr(arg->content);
		if (arg->next)
			ft_putchar(' ');
		arg = arg->next;
	}
	ft_putchar('\n');
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

void    free_all_args(t_arg **arg, int flag)
{
    if (arg && *arg)
    {
		if (flag == CHECK_PREV_ARGS)
		{
			if ((*arg)->previous)
				free_all_args(&(*arg)->previous, FALSE);
		}
        free_all_args(&(*arg)->next, flag);
        ft_strdel(&(*arg)->content);
        (*arg)->previous = NULL;
        (*arg)->next = NULL;
        (*arg)->content = NULL;
        free(*arg);
		*arg = NULL;
		arg = NULL;
    }
}

void del_one_arg(t_arg *arg, t_vect *cmd)
{
    detach_arg(arg, cmd);
    ft_strdel(&CONTENT);
    free(arg);
    arg = NULL;
}
