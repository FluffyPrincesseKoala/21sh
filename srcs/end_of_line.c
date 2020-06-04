/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:55:45 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/02 15:25:56 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int  is_pending_line(t_bash *data)
{
	return (data->expend = pending_line(LINE));
}

static void prompt_new_line(t_bash *data)
{
	ft_putchar('\n');
	data->iterator = 0;
	data->prompt_len = prompt(data->expend);
}

static void new_line(t_bash *data)
{
	if (LINE)
	{
		VECT = link_history(&VECT, NULL);
	}
	prompt_new_line(data);
}

static int  is_all_whitespaces(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// char				*pouette(char **s1, char **s2)
// {
// 	char			*new;

// 	if (s1 && s2 && s1 && s2)
// 	{
// 		if (!(new = malloc(sizeof(char) * (ft_strlen(s1)
// 			+ ft_strlen(s2) + 1))))
// 			return (NULL);
// 		new = ft_strcpy(new, s1);
// 		new = ft_strcat(new, s2);
// 		ft_strdel(&s1);
// 		ft_strdel(&s2);
// 	}
// 	else if (!s1)
// 	{
// 		new = ft_strdup(s2);
// 		ft_strdel(&s2);
// 	}
// 	else
// 	{
// 		new = ft_strdup(s1);
// 		ft_strdel(&s1);
// 	}
// 	return (new);
// }

static void update_pending_line(t_bash *data)
{
	VECT_UP->line = str_join_free(&VECT_UP->line, &LINE);
	VECT = VECT_UP;
	free_vector(&VECT_DOWN);
	VECT_DOWN = NULL;
}

int			handle_eol(t_bash *data, char *buff)
{
	/*
	** GESTION D'ERREUR !!
	*/

	if (data->expend)
	{
 //       printf("1st if eol\n");
		update_pending_line(data);  // concat previous and current line
	}
	else if (is_all_whitespaces(LINE))
	{
		printf("2nd if eol\n");
		ft_strdel(&LINE); 
	}
	if (LINE && !is_pending_line(data)) 
	{
//        printf("3rd if eol\n");
		format_line(data); 
		exec_onebyone(*data);
	}
	new_line(data);
}
