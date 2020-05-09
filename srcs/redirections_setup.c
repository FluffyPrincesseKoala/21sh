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

    new = new_redirection(cmd, SIMPLE_OUTPUT_REDIRECTION, STDOUT, STDOUT);
    operator_index = ft_stristr(arg->s, SIMPLE_OUTPUT_REDIRECTION);
    new->left_fd = search_left_fd(data, arg, operator_index, 1);
    new->right_fd = search_right_fd(data, arg, &(arg->s[operator_index + 1]));
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(data, cmd, arg, operator_index +1);
    else if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(data, arg, operator_index + 1);
    else if (new->right_fd == AMBIGUOUS)
        data->error = "error redirection ambigue";
}

static void         set_up_appending_output_redirection(
    t_bash *data, t_vect *cmd, t_arg *arg)
{
    t_redirection   *new;
    int             operator_index;
    int             substring_index;

    new = new_redirection(cmd, APPENDING_OUTPUT_REDIRECTION, STDIN, NO_RIGHT_FD);
    operator_index = ft_stristr(arg->s, APPENDING_OUTPUT_REDIRECTION);
    substring_index = operator_index + 2;
    new->left_fd = search_left_fd(data, arg, operator_index, 1);
    if (arg->s[substring_index] == '&')
        substring_index += 1;
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(data, cmd, arg, substring_index);
    else
        new->file_word = search_file_word(data, arg, substring_index);
}

static void         set_up_input_redirection(
    t_bash *data,t_vect *cmd, t_arg *current)
{
    t_redirection   *new;

    new = new_redirection(cmd, INPUT_REDIRECTION, STDIN, NO_RIGHT_FD);
    operator_index = ft_stristr(arg->s, INPUT_REDIRECTION);
    new->left_fd = search_left_fd(data, arg, operator_index, 1);
    new->right_fd = search_right_fd(data, arg, &(arg->s[operator_index + 1]));
    if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(data, arg, operator_index + 1);
    else if (new->right_fd == AMBIGUOUS)
        data->error = "error redirection ambigue";
}

static t_setup_ptr  search_redirections_in_arg(
    t_redirection_set_up *redirections_set_up, char *arg)
{
    int     i;

    i = 0;
    while (redirections_set_up[i])
    {
        if (ft_strstr(arg, redirections_set_up[i]->operator))
            return redirections_set_up[i]->f;
        i++;
    }
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
            del_arg(current);
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
    functions_ptr[0].f = &set_up_appending_output_redirection;
    functions_ptr[0].operator = APPENDING_OUTPUT_REDIRECTION;
    functions_ptr[1].f = &set_up_simple_output_redirection;
    functions_ptr[1].operator = SIMPLE_OUTPUT_REDIRECTION;
    functions_ptr[2].f = &set_up_input_redirection;
    functions_ptr[2].operator = INPUT_REDIRECTION;
    data->redirections_set_up = functions_ptr;
}