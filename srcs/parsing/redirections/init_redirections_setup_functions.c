/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections_setup_functions.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:59:13 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 21:34:31 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
** This file contains functions used to set up redirection structure in an
** appropriate way for the concerned command.
*/

/*
** Redirections in the form &>word or >&word or &>>word indicated that both
**  STDIN and STDERR are redirected to the given word.
** This function set up the two distincts redirections structures if the
**  syntax redirects STDIN and STDERR at the same time.
*/

static void	setup_stdout_and_stderr_redirection(t_vect *cmd, t_arg *arg,
	int substring_index, int *error)
{
	t_redirection	*stdout_redirection;

	stdout_redirection = cmd->redirections;
	while (stdout_redirection->next)
		stdout_redirection = stdout_redirection->next;
	if (stdout_redirection->right_fd == AMBIGUOUS)
		substring_index += 1;
	stdout_redirection->left_fd = STDOUT;
	stdout_redirection->right_fd = NO_RIGHT_FD;
	stdout_redirection->file_word = search_file_word(
			cmd, arg, substring_index, error);
	stdout_redirection->next = new_redirection(cmd, FALSE);
	stdout_redirection->next->left_fd = STDERR;
	stdout_redirection->next->right_fd = STDOUT;
}

/*
** Set left file director if any given, default is STDOUT.
** If there is a '&' instead of the file director, this mean both STDOUT and
**  STDERR will be redirected to the file word.
** Make sure there is no '&' at the right of the redirection operator.
** File word should be given in the command, if not, that's an error.
*/

static void	setup_appending_output_redirection(
	t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
	int	operator_idx;
	int	substring_idx;

	operator_idx = ft_stristr(arg->content, APPEND_OUTPUT_REDIRECTION);
	substring_idx = operator_idx + 2;
	new->left_fd = search_left_fd(cmd, arg, operator_idx, error);
	if (new->left_fd == NO_LEFT_FD)
		new->left_fd = STDOUT;
	if (arg->content[substring_idx] == '&')
		*error = NO_APPENDING_IN_FILE_DIRECTOR_ERROR;
	else if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
		setup_stdout_and_stderr_redirection(cmd, arg, substring_idx, error);
	else
		new->file_word = search_file_word(cmd, arg, substring_idx, error);
}

/*
** Set left file director if any given, default is STDOUT.
** If there is a '&' instead of the file director, this mean both STDOUT and
**  STDERR will be redirected to the file word.
** Set right file director if any given. If there is no right file_director,
**  and no indication to close the left one, search for a file word. If there
**  is no file word, that's an error.
** If there is a misused '&' right after the redirection operator, there might
**  be an ambiguous syntax in the submitter command.
*/

static void	setup_simple_output_redirection(
	t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
	int	operator_idx;
	int	substring_idx;

	operator_idx = ft_stristr(arg->content, SIMPLE_OUTPUT_REDIRECTION);
	substring_idx = operator_idx + 1;
	new->left_fd = search_left_fd(cmd, arg, operator_idx, error);
	if (new->left_fd == NO_LEFT_FD)
		new->left_fd = STDOUT;
	new->right_fd = search_right_fd(cmd, arg,
			&(arg->content[substring_idx]), error);
	if (is_stdout_and_stderr_redirection(new->left_fd, new->right_fd))
		setup_stdout_and_stderr_redirection(cmd, arg, substring_idx, error);
	else if (new->right_fd == NO_RIGHT_FD)
		new->file_word = search_file_word(cmd, arg, substring_idx, error);
	else if (new->right_fd == AMBIGUOUS)
		*error = AMBIGUOUS_REDIRECTION_ERROR;
}

/*
** Set left file director if any given, default is STDIN.
** Set right file director if any given. If there is no right file director,
**  search for a file word. If there is no file word, that's an error.
** Is there is a misused '&' right after the redirection operator, there might
**  be an ambiguous syntax in the submitter command.
*/

static void	setup_input_redirection(
	t_vect *cmd, t_arg *arg, t_redirection *new, int *error)
{
	int	operator_idx;
	int	substring_idx;

	operator_idx = ft_stristr(arg->content, INPUT_REDIRECTION);
	substring_idx = operator_idx + 1;
	new->left_fd = search_left_fd(cmd, arg, operator_idx, error);
	if (new->left_fd == NO_LEFT_FD)
		new->left_fd = STDIN;
	new->right_fd = search_right_fd(cmd, arg,
			&(arg->content[substring_idx]), error);
	if (new->right_fd == NO_RIGHT_FD)
		new->file_word = search_file_word(cmd, arg, substring_idx, error);
	else if (new->right_fd == AMBIGUOUS)
		*error = AMBIGUOUS_REDIRECTION_ERROR;
}

/*
** init an array of 3 t_redirect_setup structures, that link together
**  redirection setup function with the corresponding operator characters and
**  their file opening flags.
*/

int	init_redirections_setup_functions(t_bash *data)
{
	data->redirect_setup[0] = malloc(sizeof(t_redirect_setup));
	data->redirect_setup[1] = malloc(sizeof(t_redirect_setup));
	data->redirect_setup[2] = malloc(sizeof(t_redirect_setup));
	if (!(data->redirect_setup[0]) || !(data->redirect_setup[1])
		|| !(data->redirect_setup[2]))
		return (FAIL);
	data->redirect_setup[0]->f = &setup_appending_output_redirection;
	data->redirect_setup[0]->flags = APPENDING_OUTPUT_FLAGS;
	data->redirect_setup[0]->op = ft_strdup(APPEND_OUTPUT_REDIRECTION);
	if (!(data->redirect_setup[0]->op))
		return (FAIL);
	data->redirect_setup[1]->f = &setup_simple_output_redirection;
	data->redirect_setup[1]->flags = SIMPLE_OUTPUT_FLAGS;
	data->redirect_setup[1]->op = ft_strdup(SIMPLE_OUTPUT_REDIRECTION);
	if (!(data->redirect_setup[1]->op))
		return (FAIL);
	data->redirect_setup[2]->f = &setup_input_redirection;
	data->redirect_setup[2]->flags = INPUT_FLAGS;
	data->redirect_setup[2]->op = ft_strdup(INPUT_REDIRECTION);
	if (!(data->redirect_setup[2]->op))
		return (FAIL);
	data->redirect_setup[3] = NULL;
	return (SUCCESS);
}
