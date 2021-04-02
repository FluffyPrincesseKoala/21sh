/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:29:03 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/02 19:03:49 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	countchar(int n)
{
	int	count;

	if (n == -2147483648)
		return (11);
	if (n == 0 || n == -0)
		return (1);
	count = 0;
	if (n < 0)
	{
		n = -n;
		count += 1;
	}
	while (n >= 1)
	{
		count += 1;
		n = n / 10;
	}
	return (count);
}

static char	*putinchar(int n, char *ret, int i)
{
	if (n == -0)
		ret[0] = '0';
	else if (n < 0)
	{
		ret[0] = '-';
		if (n == -2147483648)
		{
			ret[1] = '2';
			ret = putinchar(147483648, ret, i);
		}
		else
			ret = putinchar(-n, ret, i);
	}
	else
	{
		if (n > 9)
			ret = putinchar(n / 10, ret, i - 1);
		ret[i] = (n % 10) + 48;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;

	i = countchar(n);
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = '\0';
	ret = putinchar(n, ret, i - 1);
	return (ret);
}
