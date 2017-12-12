/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:35:00 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:48 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				nblen(long long int value, int base)
{
	int	size;

	size = 0;
	if (value == 0)
		return (1);
	base *= (base < 0) ? -1 : 1;
	while (value != 0)
	{
		value /= base;
		size++;
	}
	return (size);
}

static char		basing(long long int nb, int base)
{
	char	b;

	b = (base < 0) ? 'A' : 'a';
	base *= (base < 0) ? -1 : 1;
	nb %= base;
	if (nb < 10)
		return (nb + '0');
	nb %= 10;
	return (b + nb);
}

char			*ft_itoa_base(long long int value, int base)
{
	char	*res;
	int		sign;
	int		size;
	int		i;

	sign = 0;
	if (value == 0)
		return (ft_strdup("0"));
	if (value < 0)
		sign += (base == 10) ? 1 : 0;
	size = nblen(value, base);
	if (!(res = (char *)ft_memalloc(size + sign + 1)))
		return (NULL);
	i = size + sign - 1;
	while (value != 0)
	{
		res[i] = basing(value, base);
		value /= (base < 0) ? -base : base;
		i--;
	}
	res[i] = (sign == 1) ? '-' : res[i];
	res[size] = '\0';
	return (res);
}
