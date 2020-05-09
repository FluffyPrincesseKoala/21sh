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

int     search_left_fd(t_bash *data, t_arg *arg, int operator_index, int default)
{
    char *substring;

    if (operator_index > 0)
    {
        if (!substring = ft_strsub(arg->s, 0, operator_index))
                data->error = "error malloc";
        else if (ft_str_is_digits(substring))
            return ft_atoi(substring);
        else if (ft_strlen(substring) == 1 && substring[0] == '&')
            return (STDOUT_AND_STDERR)
        else
            if (!insert_new_arg(arg->previous, substring))
                data->error = "error malloc";
        ft_strdel(substring);
    }
    return default;
}

int     search_right_fd(t_bash *data, t_arg *arg, char *substring)
{
    if (substring[0] == '&')
    {
        if (ft_str_is_digits(&(substring[1])))
            return ft_atoi(&(substring[1]))
        else if (substring[1] == CLOSE_DIRECTION)
        {
            if (ft_strlen(substring != 2))
                if (!insert_new_arg(
                    arg, ft_strsub(substring, 2, ft_strlen(ft_strsub))))
                    data->error = "error malloc";
            return CLOSE_FD;
        }
        else
            return (AMBIGUOUS)
    }
    return (NO_RIGHT_FD)
}

char    *search_file_word(t_bash *data, t_arg *arg, int substring_index)
{
    char *file;

    file = NULL;
    if (substring_index != ft_strlen(arg->s))
        if (!file = ft_strsub(arg->s, substring_index, ft_strlen(arg->s)))
            data->error = "error malloc"
    else if (arg->next)
    {
        if(!file = ft_strdup(arg->next->s))
            data->error = "error malloc";
        del_arg(arg->next)
    }
    else
        data->error = "error fin de commande innatendue"
    return file;
}

int     is_stdout_and_stderr_redirection(left_fd, right_fd)
{
    if (left_fd == STDOUT_AND_STDERR && right_fd == NO_RIGHT_FD)
        return TRUE;
    else if (left_fd == STDOUT && right_fd == AMBIGUOUS)
        return TRUE;
    else 
        return FALSE;
}

void    set_up_stdout_and_stderr_redirection(t_bash *data, t_vect *cmd,
    t_arg *arg, int substring_index)
{
    t_redirection   *stdout_redirection;

    stdout_redirection = cmd->redirections;
    while (stdout_redirection->next)
        stdout_redirection = stdout_redirection->next;
    if (stdout_redirection->right_fd == AMBIGUOUS)
        substring_index += 1;
    stdout_redirection->left_fd = STDOUT;
    stdout_redirection->right_fd = NO_RIGHT_FD;
    stdout_redirection->file_word = search_file_word(data, arg, substring_index);
    stdout_redirection->next = new_redirection(
        cmd, SIMPLE_OUTPUT_REDIRECTION, STDERR, STDOUT);
}
