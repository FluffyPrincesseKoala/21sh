/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:55:45 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/01 16:17:14 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int  is_pending_line(t_bash *data)
{
    return (data->expend = pending_line(LINE))
}

static void prompt_new_line(t_bash *data)
{
    ft_putchar('\n');
	data->iterator = 0;
	data->prompt_len = prompt(data->expend);
}

static int  is_all_whitespaces(char *str)
{
    return (str && (count_delim(str, ' ') != ft_strlen(str)));
}

static void delete_empty_line(t_bash *data)
{
    if (is_all_whitespaces(LINE))
        ft_strdel(&LINE);
}

static void update_pending_line(t_bash *data)
{
    VECT_UP->line = str_join_free(VECT_UP->line, LINE);
    VECT = VECT_UP;
    free_vector(&VECT_DOWN);
    VECT_DOWN = NULL;
}

int         handle_eol(t_bash *data, char *buff)
{
    /*
    ** GESTION D'ERREUR !!
    ** 1 commande en attente ? si oui concat et update l'historique
    ** 2 add to historic
    ** 3 mettre en attente ? si oui:  stop
    ** 4 ; \n | separators : pas prendre en compte ce qui est entre quote
    ** 5 parser les commandes une par une 
    ** 6 envoyer au process d'execution
    */

    if (data->expend)
        update_pending_line(data);  // 1
    else
        delete_empty_line(data); // 2
	if (LINE && !is_pending_line(data)) // 3 opened quote
    {
        data->vector = format_line(data); // 4 & 5
        exec_one_by_one(*data);
		data->iterator = 0;
		data->prompt_len = prompt();
    }
	prompt_new_line(data);
}
