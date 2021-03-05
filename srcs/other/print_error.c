/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koala <koala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:27:52 by koala             #+#    #+#             */
/*   Updated: 2021/03/05 19:30:50 by koala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void		put_error_msg(char *error)
{
	if (error)
	{
		ft_putstr_fd(RED, STDERR);
		ft_putstr_fd(error, STDERR);
		ft_putstr_fd(RESET, STDERR);
	}
}

void		puterror(int error)
{
	ft_putstr_fd(RED, STDERR);
	ft_putnbr_fd(error, STDERR);
	ft_putstr_fd(RESET, STDERR);
}

void		print_failed_fork_error(pid_t pid)
{
	ft_putstr_fd("fork failed at ", 2);
	ft_putnbr_fd((int)pid, 2);
	ft_putchar('\n');
	exit(-1);
}

void		error_code_to_message(int *error)
{
	if (*error)
		put_error_msg("21sh:\t");
	if (*error == MALLOC_ERROR)
		put_error_msg("Malloc failed.\n");
	if (*error == AMBIGUOUS_REDIRECTION_ERROR)
		put_error_msg("Redirection syntax ambiguous.\n");
	if (*error == UNEXPECT_COMMAND_END_ERROR)
		put_error_msg("Unexpected end of command.\n");
	if (*error == OPEN_ERROR)
		put_error_msg("Open failed.\n");
	if (*error == NO_APPENDING_IN_FILE_DIRECTOR_ERROR)
		put_error_msg("Unexpected '&' symbole for appending output redirection.\n");
	if (*error == SNTX_ERR)
		put_error_msg("Unexpected end of command.\n");
	if (*error == ENV_FAIL)
		put_error_msg("find required value in env\n");
	*error = 0;
}