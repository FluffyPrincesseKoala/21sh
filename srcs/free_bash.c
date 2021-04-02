/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:57:42 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 18:12:24 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

static void	free_redirect_setup(t_redirect_setup **redirect_setup)
{
	int		i;

	if (redirect_setup)
	{
		i = 0;
		while (redirect_setup[i])
		{
			ft_strdel(&redirect_setup[i]->op);
			free(redirect_setup[i]);
			i++;
		}
		free(redirect_setup);
	}
}

static void	free_all_vectors(t_vect *vect)
{
	if (vect)
	{
		ft_strdel(&vect->line);
		ft_strdel(&vect->eof);
		free_array(vect->doc_string);
		free_all_args(&vect->args, FALSE);
		free_all_vectors(vect->next);
		free_all_vectors(vect->up);
		if (vect->redirections)
			free_redirections(vect);
		vect->args = NULL;
		vect->next = NULL;
		vect->up = NULL;
		vect->down = NULL;
		vect->redirections = NULL;
		vect->line = NULL;
		free(vect);
		vect = NULL;
	}
}

static void	free_builtin(t_built **fct)
{
	int		i;

	i = 0;
	while (i != NB_BUILTIN && *fct)
	{
		ft_strdel(&(*fct)[i].name);
		(*fct)[i].name = NULL;
		(*fct)[i].f = NULL;
		i++;
	}
	free(*fct);
	*fct = NULL;
	fct = NULL;
}

void	*free_bash(t_bash *data)
{
	if (data->env)
		free_array(data->env);
	if (data->args_array)
		free_array(data->args_array);
	data->env = NULL;
	data->venv = NULL;
	free_all_vectors(data->vector);
	free_redirect_setup(data->redirect_setup);
	data->redirect_setup = NULL;
	free_builtin(&data->builtin);
	ft_strdel(&data->eof);
	ft_strdel(&data->copied);
	ft_strdel(&data->path);
	free(data);
	data = NULL;
	termi(NULL, NULL);
	return (NULL);
}
