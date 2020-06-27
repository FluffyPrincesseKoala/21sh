/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/27 09:38:06 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"


static void         set_up_simple_output_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, char *error)
{
    int             operator_index;
    int             substring_index;

    operator_index = ft_stristr(arg->content, SIMPLE_OUTPUT_REDIRECTION);
    substring_index = operator_index + 1;
    new->left_fd = search_left_fd(arg, operator_index, STDOUT, error);
    new->right_fd = search_right_fd(arg, &(arg->content[substring_index]), error);
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(cmd, arg, substring_index, error);
    else if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(cmd, arg, substring_index, error);
    else if (new->right_fd == AMBIGUOUS)
        ft_strcpy("error redirection ambigue", error);
}

static void         set_up_appending_output_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, char *error)
{
    int             operator_index;
    int             substring_index;

    operator_index = ft_stristr(arg->content, APPENDING_OUTPUT_REDIRECTION);
    substring_index = operator_index + 2;
    new->left_fd = search_left_fd(arg, operator_index, STDOUT, error);
    if (arg->content[substring_index] == '&')
        substring_index += 1;
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(cmd, arg, substring_index, error);
    else
        new->file_word = search_file_word(cmd, arg, substring_index, error);
}

static void         set_up_input_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, char *error)
{
    int operator_index;
    int substring_index;

    operator_index = ft_stristr(arg->content, INPUT_REDIRECTION);
    substring_index = operator_index + 1;
    new->left_fd = search_left_fd(arg, operator_index, STDIN, error);
    new->right_fd = search_right_fd( arg, &(arg->content[substring_index]), error);
    if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(cmd, arg, substring_index, error);
    else if (new->right_fd == AMBIGUOUS)
        ft_strcpy("error redirection ambigue", error);
}

t_redirection_setup    *search_redirections_in_arg(
    t_redirection_setup **redirections_set_up, char *arg)
{
    int     i;

    if (arg)
    {
        i = 0;
        while (redirections_set_up[i])
        {
            if (ft_strstr(arg, redirections_set_up[i]->op))
                return (redirections_set_up[i]);
            i++;
        }
    }
    return (NULL);
}

void                search_redirections_in_cmd(t_bash *data, t_vect *cmd)
{
    t_redirection_setup *setup_redirection;
    t_arg               *arg;

    arg = cmd->args;
    while (arg)
    {
        if (setup_redirection = search_redirections_in_arg(
            data->redirections_setup, arg->content))
        {
            setup_redirection->f(
                cmd, arg, new_redirection(cmd, setup_redirection->flags), data->error);
            del_one_arg(arg, cmd);
            arg = cmd->args;
        }
        else
            arg = arg->next;
        if (error_occured(data->error))
            arg = NULL;
    }
}

t_bash          *initialize_redirection_set_up_functions(t_bash *data)
{
    if (!(data->redirections_setup[0] = malloc(sizeof(t_redirection_setup))))
        return (NULL);
    data->redirections_setup[0]->f = &set_up_appending_output_redirection;
    if (!(data->redirections_setup[0]->op = ft_strdup(APPENDING_OUTPUT_REDIRECTION)))
        return (NULL);
    data->redirections_setup[0]->flags = APPENDING_OUTPUT_FLAGS;
    if (!(data->redirections_setup[1] = malloc(sizeof(t_redirection_setup))))
        return (NULL);
    data->redirections_setup[1]->f = &set_up_simple_output_redirection;
    if (!(data->redirections_setup[1]->op = ft_strdup(SIMPLE_OUTPUT_REDIRECTION)))
        return (NULL);
    data->redirections_setup[1]->flags = SIMPLE_OUTPUT_FLAGS;
    if (!(data->redirections_setup[2] = malloc(sizeof(t_redirection_setup))))
        return (NULL);
    data->redirections_setup[2]->f = &set_up_input_redirection;
    if (!(data->redirections_setup[2]->op = ft_strdup(INPUT_REDIRECTION)))
        return (NULL);
    data->redirections_setup[2]->flags = INPUT_FLAGS;
    data->redirections_setup[3] = NULL;
}