/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code_to_message.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:19:03 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 20:26:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

void	error_code_to_message(int *error)
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
		put_error_msg("Unexpected '&' symbole for appending output redirect\n");
	if (*error == SNTX_ERR)
		put_error_msg("Unexpected end of command.\n");
	if (*error == ENV_FAIL)
		put_error_msg("find required value in env\n");
	*error = 0;
}
