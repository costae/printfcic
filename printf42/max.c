/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:35:03 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:36:00 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		get_maxstrlen(t_char string, char *flag, int *prec)
{
	int	max;

	max = 0;
	if (flag[4] == 's' && !flag[3])
		max = ft_strlen(string.str);
	else if (flag[4] == 'S' || (flag[3] == 'l' && flag[4] == 's'))
		max = ft_wstrlen(string.wstr, prec[1]);
	else if (flag[4] == 'c' && !flag[3])
		max = 1;
	else
	{
		if (string.wchar <= 0x7F)
			max = 1;
		else if (string.wchar <= 0x7FF)
			max = 2;
		else if (string.wchar <= 0xFFFF)
			max = 3;
		else
			max = 4;
	}
	if (prec[1] >= 0 && flag[4] != 'c' && flag[4] != 'C')
		return (max > prec[1] ? prec[1] : max);
	else
		return (max);
}

int		get_maxnbrlen(long long int nbr, char *flag, int *prec)
{
	int		max;
	int		len;

	len = (nbr < 0) ? 1 : 0;
	set_base(flag, prec);
	if (ft_strindexof("dDi", flag[4]) != -1)
		len += nblen(nbr, prec[2]);
	else
		len = unblen((unsigned long long)nbr, prec[2]);
	max = (len > prec[1]) ? len : prec[1];
	if (max == prec[1] && !prec[0] && (flag[4] == 'o' || flag[4] == 'O'))
		max--;
	if ((flag[0] == '#' && (flag[4] == 'o' || flag[4] == 'O')) ||
			(flag[2] && flag[4] != '%'))
		max++;
	if ((flag[0] == '#' && (flag[4] == 'x' || flag[4] == 'X')) ||
			flag[4] == 'p')
		max += 2;
	if (!nbr && !prec[1])
		max--;
	return (max);
}
