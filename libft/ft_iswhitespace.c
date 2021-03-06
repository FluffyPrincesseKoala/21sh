/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:44:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/03/06 12:37:53 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iswhitespace(int c)
{
	if (c == '\n')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\r')
		return (1);
	else
		return (0);
}
