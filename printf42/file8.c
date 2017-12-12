/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:35:02 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:55 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_power(int n, int pow)
{
	if (pow <= 0)
		return (1);
	else if (pow == 1)
		return (n);
	else
		return (n * ft_power(n, pow - 1));
}
