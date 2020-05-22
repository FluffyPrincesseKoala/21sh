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
    t_bash *data, t_vect *cmd, t_arg *arg, t_redirection *new)
{
    int             operator_index;
    int             substring_index;

    operator_index = ft_stristr(arg->s, SIMPLE_OUTPUT_REDIRECTION);
    substring_index = operator_index + 1;
    new->left_fd = search_left_fd(data, arg, operator_index, STDOUT);
    new->right_fd = search_right_fd(data, arg, &(arg->s[substring_index]));
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(data, cmd, arg, substring_index);
    else if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(data, arg, substring_index);
    else if (new->right_fd == AMBIGUOUS)
        data->error = "error redirection ambigue";
}

static void         set_up_appending_output_redirection(
    t_bash *data, t_vect *cmd, t_arg *arg, t_redirection *new)
{
    int             operator_index;
    int             substring_index;

    operator_index = ft_stristr(arg->s, APPENDING_OUTPUT_REDIRECTION);
    substring_index = operator_index + 2;
    new->left_fd = search_left_fd(data, arg, operator_index, STD);
    if (arg->s[substring_index] == '&')
        substring_index += 1;
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(data, cmd, arg, substring_index);
    else
        new->file_word = search_file_word(data, arg, substring_index);
}

static void         set_up_input_redirection(
    t_bash *data, t_vect *cmd, t_arg *arg, t_redirection *new)
{
    int operator_index;
    int substring_index;

    operator_index = ft_stristr(arg->s, INPUT_REDIRECTION);
    substring_index = operator_index + 1;
    new->left_fd = search_left_fd(data, arg, operator_index, STDIN);
    new->right_fd = search_right_fd(data, arg, &(arg->s[substring_index]));
    if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(data, arg, substring_index);
    else if (new->right_fd == AMBIGUOUS)
        data->error = "error redirection ambigue";
}

t_redirection_set_up    *search_redirections_in_arg(
    t_redirection_set_up *redirections_set_up, char *arg)
{
    int     i;

    i = 0;
    while (redirections_set_up[i])
    {
        if (ft_strstr(arg, redirections_set_up[i].operator))
            return &(redirections_set_up[i]);
        i++;
    }
    return NULL
}

void                search_redirections_in_cmd(t_bash *data, t_vect *cmd)
{
    t_setup_ptr set_up_redirection;
    t_arg       *current;

    current = cmd->args;
    while (current)
    {
        if (set_up_redirection = search_redirections_in_arg(current->s))
        {
            set_up_redirection->f(
                cmd, current, new_redirection(cmd, set_up_redirection->flags));
            del_arg(current);
            current = cmd->args;
        }
        else
            current = current->next;
        if (error_occured(data->error))
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
    functions_ptr[0].flags = APPENDING_OUTPUT_FLAGS;
    functions_ptr[1].f = &set_up_simple_output_redirection;
    functions_ptr[1].operator = SIMPLE_OUTPUT_REDIRECTION;
    functions_ptr[1].flags = SIMPLE_OUTPUT_FLAGS;
    functions_ptr[2].f = &set_up_input_redirection;
    functions_ptr[2].operator = INPUT_REDIRECTION;
    functions_ptr[2].flags = INPUT_FLAGS;
    data->redirections_set_up = functions_ptr;
}