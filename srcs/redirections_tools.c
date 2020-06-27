/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2020/06/27 09:07:12 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int     search_left_fd(t_arg *arg, int operator_index, int def, char *error)
{
    char *substring;

    if (operator_index > 0)
    {
        if (!(substring = ft_strsub(arg->content, 0, operator_index)))
                ft_strcpy("error malloc", error);
        else if (ft_str_is_digits(substring))
            return ft_atoi(substring);
        else if (ft_strlen(substring) == 1 && substring[0] == '&')
            return (STDOUT_AND_STDERR);
        else
            if (!insert_new_arg(arg->previous, substring))
                ft_strcpy("error malloc", error);
        ft_strdel(&substring);
    }
    return def;
}

int     search_right_fd(t_arg *arg, char *substring, char *error)
{
    if (substring[0] == '&')
    {
        if (ft_str_is_digits(&(substring[1])))
            return ft_atoi(&(substring[1]));
        else if (substring[1] == CLOSE_DIRECTION)
        {
            if (ft_strlen(substring) != 2)
                if (!insert_new_arg(
                    arg, ft_strsub(substring, 2, ft_strlen(substring) - 2)));
                    ft_strcpy("error malloc", error);
            return (CLOSE_FD);
        }
        else
            return (AMBIGUOUS);
    }
    return (NO_RIGHT_FD);
}

char    *search_file_word(t_vect *cmd, t_arg *arg, int substring_index, char *error)
{
    char *file;

    file = NULL;
    if (substring_index != ft_strlen(arg->content))
    {
        if (!(file = ft_strsub(arg->content, substring_index, ft_strlen(arg->content))))
            ft_strcpy("error malloc", error);
    }
    else if (arg->next && arg->next->content)
    {
        if(!(file = ft_strdup(arg->next->content)))
            ft_strcpy("error malloc", error);
        del_one_arg(arg->next, cmd);
    }
    else
        ft_strcpy("error fin de commande innatendue", error);
    return file;
}

int     is_stdout_and_stderr_redirection(int left_fd,int right_fd)
{
    if (left_fd == STDOUT_AND_STDERR && right_fd == NO_RIGHT_FD)
        return TRUE;
    else if (left_fd == STDOUT && right_fd == AMBIGUOUS)
        return TRUE;
    else 
        return FALSE;
}

void    set_up_stdout_and_stderr_redirection(t_vect *cmd, t_arg *arg, 
    int substring_index, char *error)
{
    t_redirection   *stdout_redirection;

    stdout_redirection = cmd->redirections;
    while (stdout_redirection->next)
        stdout_redirection = stdout_redirection->next;
    if (stdout_redirection->right_fd == AMBIGUOUS)
        substring_index += 1;
    stdout_redirection->left_fd = STDOUT;
    stdout_redirection->right_fd = NO_RIGHT_FD;
    stdout_redirection->file_word = search_file_word(cmd, arg, substring_index, error);
    stdout_redirection->next = new_redirection(cmd, SIMPLE_OUTPUT_FLAGS);
    stdout_redirection->next->left_fd = STDERR;
    stdout_redirection->next->right_fd = STDOUT;
}
