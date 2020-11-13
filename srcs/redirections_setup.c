/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/07/10 13:57:52 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"


static void         set_up_simple_output_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
    int             operator_index;
    int             substring_index;

    operator_index = ft_stristr(CONTENT, SIMPLE_OUTPUT_REDIRECTION);
    substring_index = operator_index + 1;
    new->left_fd = search_left_fd(arg, operator_index, STDOUT, error);
    new->right_fd = search_right_fd(arg, &(CONTENT[substring_index]), error);
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(cmd, arg, substring_index, error);
    else if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(cmd, arg, substring_index, error);
    else if (new->right_fd == AMBIGUOUS)
        *error = AMBIGUOUS_REDIRECTION_ERROR;
}

static void         set_up_appending_output_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
    int             operator_index;
    int             substring_index;

    operator_index = ft_stristr(CONTENT, APPENDING_OUTPUT_REDIRECTION);
    substring_index = operator_index + 2;
    new->left_fd = search_left_fd(arg, operator_index, STDOUT, error);
    if (CONTENT[substring_index] == '&')
        substring_index += 1;
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(cmd, arg, substring_index, error);
    else
        new->file_word = search_file_word(cmd, arg, substring_index, error);
}

static void         set_up_input_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
    int operator_index;
    int substring_index;

    operator_index = ft_stristr(CONTENT, INPUT_REDIRECTION);
    substring_index = operator_index + 1;
    new->left_fd = search_left_fd(arg, operator_index, STDIN, error);
    new->right_fd = search_right_fd( arg, &(CONTENT[substring_index]), error);
    if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(cmd, arg, substring_index, error);
    else if (new->right_fd == AMBIGUOUS)
        *error = AMBIGUOUS_REDIRECTION_ERROR;
}

void            set_up_pipe_redirection(t_redirection *new)
{
    new->left_fd = 1;
    new->right_fd = 0;
}

t_bash          *initialize_redirection_set_up_functions(t_bash *data)
{
    int i;

    i = -1;
    while (++i < 3)
        if (!(REDIRECTION_SETUP[i] = malloc(sizeof(t_redirection_setup))))
            return (NULL);
    REDIRECTION_SETUP[0]->f = &set_up_appending_output_redirection;
    REDIRECTION_SETUP[0]->flags = APPENDING_OUTPUT_FLAGS;
    if (!(REDIRECTION_SETUP[0]->op = ft_strdup(APPENDING_OUTPUT_REDIRECTION)))
        return (NULL);
    REDIRECTION_SETUP[1]->f = &set_up_simple_output_redirection;
    REDIRECTION_SETUP[1]->flags = SIMPLE_OUTPUT_FLAGS;
    if (!(REDIRECTION_SETUP[1]->op = ft_strdup(SIMPLE_OUTPUT_REDIRECTION)))
        return (NULL);
    REDIRECTION_SETUP[2]->f = &set_up_input_redirection;
    REDIRECTION_SETUP[2]->flags = INPUT_FLAGS;
    if (!(REDIRECTION_SETUP[2]->op = ft_strdup(INPUT_REDIRECTION)))
        return (NULL);
    REDIRECTION_SETUP[3] = NULL;
}