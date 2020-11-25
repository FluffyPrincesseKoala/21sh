/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:23:17 by cylemair          #+#    #+#             */
/*   Updated: 2020/11/25 11:20:15 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void print_args(t_bash *data)
{
	VECT->args = VECT->args->next;
	while (VECT->args)
	{
		ft_putstr(VECT->args->content);
		if (VECT->args->next)
			ft_putchar(' ');
		VECT->args = VECT->args->next;
	}
	ft_putchar('\n');
}

int     check_built_in(t_bash *data)
{
    if (ft_strnequ(data->vector->args->content, "exit", 4))
	{
		return (-1);
	}
	if (ft_strnequ(data->vector->args->content, "setenv", 6))
	{
		set_env(data);
        return (1);
	}
	if (ft_strnequ(data->vector->args->content, "unsetenv", 8))
	{
		unset_env(data);
        return (1);
	}
	if (ft_strnequ(data->vector->args->content, "cd", 2))
	{
		change_directory(data);
		return (1);
	}
	if (ft_strnequ(data->vector->args->content, "echo", 4))
	{
		print_args(data);
		return (1);
	}
    return (0);
}