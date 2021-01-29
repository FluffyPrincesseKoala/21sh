/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/29 11:36:28 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** This file contains functions used to set up redirection structure in an
** appropriate way for the concerned command.
*/

/*
** Set left file director if any given, default is STDOUT.
** If there is a '&' instead of the file director, this mean both STDOUT and
**  STDERR will be redirected to the file word.
** Make sure there is no '&' at the right of the redirection operator.
** File word should be given in the command, if not, that's an error.
*/

static void         set_up_appending_output_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
    int             operator_idx;
    int             substring_idx;

    operator_idx = ft_stristr(CONTENT, APPENDING_OUTPUT_REDIRECTION);
    substring_idx = operator_idx + 2;
    new->left_fd = search_left_fd(cmd, arg, operator_idx, error);
    if (new->left_fd == NO_LEFT_FD)
        new->left_fd = STDOUT;
    if (CONTENT[substring_idx] == '&')
        *error = NO_APPENDING_IN_FILE_DIRECTOR_ERROR;
    else if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(cmd, arg, substring_idx, error);
    else
        new->file_word = search_file_word(cmd, arg, substring_idx, error);
}

/*
** Set left file director if any given, default is STDOUT.
** If there is a '&' instead of the file director, this mean both STDOUT and
**  STDERR will be redirected to the file word.
** Set right file director if any given. If there is no right file_director, and
**  no indication to close the left one, search for a file word. If there is no
**  file word, that's an error.
** If there is a misused '&' right after the redirection operator, there might
**  be an ambiguous syntax in the submitter command.
*/

static void         set_up_simple_output_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
    int             operator_idx;
    int             substring_idx;

    operator_idx = ft_stristr(CONTENT, SIMPLE_OUTPUT_REDIRECTION);
    substring_idx = operator_idx + 1;
    new->left_fd = search_left_fd(cmd, arg, operator_idx, error);
    if (new->left_fd == NO_LEFT_FD)
        new->left_fd = STDOUT;
    new->right_fd = search_right_fd(cmd, arg, &(CONTENT[substring_idx]), error);
    if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
        set_up_stdout_and_stderr_redirection(cmd, arg, substring_idx, error);
    else if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(cmd, arg, substring_idx, error);
    else if (new->right_fd == AMBIGUOUS)
        *error = AMBIGUOUS_REDIRECTION_ERROR;
}

static void         set_up_input_redirection(
    t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
    int operator_idx;
    int substring_idx;

    operator_idx = ft_stristr(CONTENT, INPUT_REDIRECTION);
    substring_idx = operator_idx + 1;
    new->left_fd = search_left_fd(cmd, arg, operator_idx, error);
    if (new->left_fd == NO_LEFT_FD)
        new->left_fd = STDIN;
    new->right_fd = search_right_fd(cmd, arg, &(CONTENT[substring_idx]), error);
    if (new->right_fd == NO_RIGHT_FD)
        new->file_word = search_file_word(cmd, arg, substring_idx, error);
    else if (new->right_fd == AMBIGUOUS)
        *error = AMBIGUOUS_REDIRECTION_ERROR;
}

void            set_up_pipe_redirection(t_redirection *new)
{
    new->left_fd = 1;
    new->right_fd = 0;
}

int         initialize_redirection_set_up_functions(t_bash *data)
{
    int i;

    i = -1;
    while (++i < 3)
        if (!(REDIRECTIONS_SETUP[i] = malloc(sizeof(t_redirection_setup))))
            return (FAIL);
    REDIRECTIONS_SETUP[0]->f = &set_up_appending_output_redirection;
    REDIRECTIONS_SETUP[0]->flags = APPENDING_OUTPUT_FLAGS;
    if (!(REDIRECTIONS_SETUP[0]->op = ft_strdup(APPENDING_OUTPUT_REDIRECTION)))
        return (FAIL);
    REDIRECTIONS_SETUP[1]->f = &set_up_simple_output_redirection;
    REDIRECTIONS_SETUP[1]->flags = SIMPLE_OUTPUT_FLAGS;
    if (!(REDIRECTIONS_SETUP[1]->op = ft_strdup(SIMPLE_OUTPUT_REDIRECTION)))
        return (FAIL);
    REDIRECTIONS_SETUP[2]->f = &set_up_input_redirection;
    REDIRECTIONS_SETUP[2]->flags = INPUT_FLAGS;
    if (!(REDIRECTIONS_SETUP[2]->op = ft_strdup(INPUT_REDIRECTION)))
        return (FAIL);
    REDIRECTIONS_SETUP[3] = NULL;
    return (SUCCESS);
}