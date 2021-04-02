/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlendelim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:37:15 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/01 22:13:20 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlendelim(char *str, char delim, int start)
{
	int	i;

	i = 0;
	if (str[start] == delim)
		i = 1;
	while (str && str[i + start] && str[i + start] != delim)
		i++;
	return (i);
}
