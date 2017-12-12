/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:35:03 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:36:02 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_str(char *flag, int *prec, t_char string)
{
	int	total;

	total = get_maxstrlen(string, flag, prec);
	if (flag[4] == 's' && prec[1] && !flag[3] && string.str == NULL)
		total = 6;
	set_undefined(NULL, flag, prec, total);
	if (flag[4] == 's' && !flag[3])
		total == 0 ? ft_putlenstr(NULL, -1) : ft_putlenstr(string.str, total);
	else if (flag[4] == 'c' && !flag[3])
		ft_putchar(string.c);
	else if (flag[4] == 'S' || (flag[3] == 'l' && flag[4] == 's'))
	{
		if (total == -1)
		{
			ft_putlenstr("(null)", 6);
			total = 6;
		}
		else
			ft_putwstr(string.wstr, total);
	}
	else
		ft_putwchar(string.wchar);
	prec[3] += total > prec[0] ? total : prec[0];
	if (flag[1] == '-')
		ft_putnchar(' ', prec[0] - total);
}

void	print_nbr(char *flag, int *prec, long long int nbr)
{
	int	max;

	if (!nbr && flag[4] != 'o' && flag[4] != 'O')
		flag[0] = 0;
	if (!nbr && prec[1] == -1 && flag[4] == 'o' && flag[0] == '#')
		prec[1] = 0;
	max = get_maxnbrlen(nbr, flag, prec);
	prec[3] += BIGGER(max, BIGGER(prec[0], prec[1]));
	print_flag(flag, prec, max, nbr);
	if (prec[2] == 16 && flag[4] == 'X')
		prec[2] = 1;
	if (flag[4] == '%')
		write(1, "%", 1);
	if ((nbr || prec[1]) && flag[4] != '%')
		print_base(prec[2], nbr, flag);
	if (flag[1] == '-' && prec[0] > prec[1])
		ft_putnchar(' ', prec[0] - max);
}

void	print_flag(char *flag, int *prec, int max, long long int nbr)
{
	if ((!flag[1] || (flag[1] == '0' && prec[1] >= 0)))
		ft_putnchar(' ', prec[0] - max);
	if (flag[2] && flag[4] != '%')
		write(1, &flag[2], 1);
	if ((flag[0] == '#'
				&& (flag[4] == 'X' || flag[4] == 'x')) || flag[4] == 'p')
		flag[4] == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
	if (flag[0] == '#' && (flag[4] == 'o' || flag[4] == 'O'))
	{
		write(1, "0", 1);
		prec[1] -= prec[1] > 0 ? 1 : 0;
	}
	if (flag[1] == '0' && prec[1] == -1)
		ft_putnchar('0', prec[0] - max);
	if (prec[1] > 0)
		ft_putnchar('0', prec[1] - nblen(nbr, prec[2]));
}

void	print_base(int base, long long int nbr, char *flag)
{
	char	*out;

	if (base == 1)
		base = -16;
	if (ft_strindexof("dDi", flag[4]) != -1)
		out = (nbr == -9223372036854775807 - 1) ?
			ft_strdup("-9223372036854775808") : ft_itoa_base(nbr, base);
	else
		out = ft_uitoa_base((unsigned long long int)nbr, base);
	ft_putlenstr(out, ft_strlen(out));
	ft_memdel((void *)&out);
}
