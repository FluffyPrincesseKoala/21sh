/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:12:00 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/15 18:12:14 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vingt_et_un_sh.h"

/*
**	create args how are badlly formated (ex: "cat<<lol")
**	by spliting on << character
*/

static int	parse_splited_heredoc(char **array, t_arg **new)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (i == 1)
			add_arg(new, create_arg(ft_strdup("<<"), NULL));
		add_arg(new, create_arg(ft_strdup(array[i]), NULL));
		i++;
	}
	return (TRUE);
}

int			format_heredoc(t_vect **vect, t_arg **to_check)
{
	t_arg	*new;
	char	**splited;
	int		len;
	int		ret;

	ret = FALSE;
	new = NULL;
	if (ft_strstr((*to_check)->content, "<<")
		&& (splited = ft_strsplit((*to_check)->content, '<')))
	{
		if ((len = ft_arraylen(splited)) >= 2)
		{
			ret = parse_splited_heredoc(splited, &new);
			free_all_args(to_check, 0);
			(*vect)->args = new;
		}
	}
	free_array(splited);
	if (ret == TRUE)
		return (TRUE);
	free_all_args(&new, 0);
	return (FALSE);
}
