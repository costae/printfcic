/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file21.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:34:56 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:40 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_wstrlen(wchar_t *ws, int max)
{
	int	i;
	int	len;

	if (!ws)
		return (-1);
	i = 0;
	len = 0;
	if (max == -1)
		max = 2147483647;
	while (ws[i])
	{
		if (len + 1 <= max && ws[i] <= 0x7F)
			len += 1;
		else if (len + 2 <= max && ws[i] <= 0x7FF)
			len += 2;
		else if (len + 3 <= max && ws[i] <= 0xFFFF)
			len += 3;
		else if (len + 4 <= max)
			len += 4;
		i++;
	}
	return (len);
}
