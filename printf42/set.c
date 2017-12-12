/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:35:03 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:06 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	set_params(int *prec, char *flag, t_char *string)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i < 3)
			prec[i] = 0;
		flag[i] = 0;
		i++;
	}
	(*string).wchar = 0;
	(*string).wstr = 0;
	(*string).c = 0;
	(*string).str = 0;
}

void	set_undefined(char **fmt, char *flag, int *prec, int total)
{
	int	i;

	if ((flag[4] == 'c' || flag[4] == 's') && !prec[1])
		prec[1] = -1;
	i = prec[0] - ((total < 0) ? 1 : total);
	if (flag[1] == '0')
		ft_putnchar('0', i);
	else if ((flag[2] == ' ' || (!flag[2])) && !flag[1])
		ft_putnchar(' ', i);
	if (prec[0] != 0 && total < 0)
		prec[3] += prec[0] + (total == -7 ? -1 : total);
	if (total == -7)
	{
		if (flag[4])
		{
			write(1, &flag[4], 1);
			prec[3]++;
			(*fmt)++;
		}
		if (flag[1] == '-' && prec[0] > prec[1])
			ft_putnchar(' ', prec[0] - (total > 0 ? total : 1));
	}
}

void	set_base(char *flag, int *prec)
{
	if (flag[4] == 'x' || flag[4] == 'X' || flag[4] == 'p')
		prec[2] = 16;
	else if (flag[4] == 'o' || flag[4] == 'O')
		prec[2] = 8;
	else
		prec[2] = 10;
	if (flag[4] == '%')
		prec[1] = -1;
}
