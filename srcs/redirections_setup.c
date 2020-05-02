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


static void         set_up_simple_output_redirection(
    t_bash *data, t_vect *cmd, t_arg *arg)
{
    t_redirection   *new;
    int             operator_index;

    new = new_redirection(cmd, 1, 1);
    operator_index = ft_stristr(arg->s, SIMPLE_OUTPUT_REDIRECTION);
    new->in_fd = search_in_fd(data, arg, operator_index, 1)
    new->out_fd = search_out_fd(data, &(arg->s[operator_index + 1]))
    if (!new->out_fd)
        new->out_file = search_out_file(data, arg, operator_index + 1)
}

static void         set_up_output_eof_redirection(
    t_bash *data, t_vect *cmd, t_arg *arg)
{
    t_redirection   *new;
    int             operator_index;
    int             substring_index;

    new = new_redirection(cmd, 1, 1);
    operator_index = ft_stristr(arg->s, OUTPUT_EOF_REDIRECTION);
    substring_index = operator_index + 1;
    new->in_fd = search_in_fd(data, arg, operator_index, 1);
    if (arg->s[substring_index] == '&')
        substring_index += 1;
    new->out_file = search_out_file(data, arg, substring_index);
}

static void         set_up_input_redirection(
    t_bash *data,t_vect *cmd, t_arg *current)
{
}

static t_setup_ptr  search_redirections_in_arg(
    t_redirection_set_up *redirections_set_up, char *arg)
{
    int     i;

    i = 0;
    while (redirections_set_up[i])
        if (ft_strstr(arg, redirections_set_up[i]->operator))
            return redirections_set_up[i]->f;
    return NULL
}

void                search_redirections_in_cmd(t_vect *cmd, t_bash *data)
{
    t_setup_ptr set_up_redirection;
    t_arg       *current;

    current = cmd->args;
    while (current)
    {
        if (set_up_redirection = search_redirections_in_arg(current->s))
        {
            set_up_redirection(cmd, current);
            current = cmd->args;
        }
        else
            current = current->next;
        if (data->error[0] != NULL)
            current = NULL;
    }
}

void                initialize_redirection_set_up_functions(t_bash *data)
{
    t_redirection_set_up    *functions_ptr;

    if (!functions_ptr = memalloc(sizeof(t_redirection_set_up) * 4))
        data->error = "error malloc"
    functions_ptr[0].f = &set_up_output_eof_redirection;
    functions_ptr[0].operator = ">>";
    functions_ptr[1].f = &set_up_simple_output_redirection;
    functions_ptr[1].operator = ">";
    functions_ptr[2].f = &set_up_input_redirection;
    functions_ptr[2].operator = "<";
    data->redirections_set_up = functions_ptr;
}