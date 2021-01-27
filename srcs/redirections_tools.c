/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/01/27 18:12:56 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** Take a look at the left of the redirection operator.
** If there is nothing, just send the given default file director.
** If there are digits only, set them as file director.
** If there is a '&', it means the redirection concerns both STDOUT and STDERR.
** Else it considers any present word as a detached argument and add it to the 
**  command argument list.
*/

int     search_left_fd(t_arg *arg, int operator_idx, int default_fd, int *error)
{
    char *substring;
	int	spell_check;

    if (operator_idx > 0)
    {
        if (!(substring = ft_strsub(CONTENT, 0, operator_idx)))
            *error = MALLOC_ERROR;
        else if (ft_str_is_digits(substring))
            return ft_atoi(substring);
        else if (ft_strlen(substring) == 1 && substring[0] == '&')
            return (STDOUT_AND_STDERR);
        else
		{
            if (!insert_new_arg(arg->previous, substring))
                *error = MALLOC_ERROR;
		}
        ft_strdel(&substring);
    }
    return default_fd;
}

/*
** Take a look at the right of the redirection operator.
** If there is no '&' this means there is no file director here.
** If there are digits only after the '&', set them as file director.
** If there is a '-' after the '&', this means the left file director needs to
**  be closed, if there still a word the '-', considers it as a detached
**  argument and add it to the command argument list.
** If there any other kind of word right after '&', this means there might be an
**  ambiguous syntax in the submitted command.
*/

int     search_right_fd(t_arg *arg, char *substring, int *error)
{
    if (substring[0] == '&')
    {
        if (ft_str_is_digits(&(substring[1])))
            return ft_atoi(&(substring[1]));
        else if (substring[1] == CLOSE_DIRECTION)
        {
            if (ft_strlen(substring) != 2)
            {
                if (!insert_new_arg(
                    arg, ft_strsub(substring, 2, ft_strlen(substring) - 2)));
                    *error = MALLOC_ERROR;
            }
            return (CLOSE_FD);
        }
        else
            return (AMBIGUOUS);
    }
    return (NO_RIGHT_FD);
}

/*
** Take a look at the right of the redirection operator.
** If any word is present, return a copy of it.
** Else, look for it in the next argument.
** If the redirection operator is the end of the command, that's an error.
*/

char    *search_file_word(
    t_vect *cmd, t_arg *arg, int substring_index, int *error)
{
    char *file;

    file = NULL;
    if (substring_index != ft_strlen(CONTENT))
    {
        if (!(file = ft_strsub(CONTENT,
            substring_index, ft_strlen(CONTENT) - substring_index)))
            *error = MALLOC_ERROR;
    }
    else if (arg->next && arg->next->content)
    {
        if(!(file = ft_strdup(arg->next->content)))
            *error = MALLOC_ERROR;
        del_one_arg(arg->next, cmd);
    }
    else
        *error = UNEXPECT_COMMAND_END_ERROR;
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
    int substring_index, int *error)
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
