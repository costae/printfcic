/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:34:56 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:08 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			convert(va_list ap, char *flag, int *prec, t_char string)
{
	long long int	ret;

	ret = 0;
	if (flag[4] == '%')
		ret = 1;
	else if (flag[4] == 'C' || (flag[3] == 'l' && flag[4] == 'c'))
		string.wchar = va_arg(ap, wchar_t);
	else if (flag[4] == 's' && flag[3] != 'l')
		string.str = va_arg(ap, const char *);
	else if (flag[4] == 'S' || (flag[3] == 'l' && flag[4] == 's'))
		string.wstr = va_arg(ap, wchar_t *);
	else if (flag[4] == 'c')
		string.c = va_arg(ap, int);
	else
		ret = convert_nb(ap, flag[4], flag);
	if (ret < 0 && ft_strindexof("dDi", flag[4]) != -1 &&
			ret != -9223372036854775807 - 1)
	{
		flag[2] = '-';
		ret *= -1;
	}
	if (ft_strindexof("pdDioOuUxX%", flag[4]) != -1)
		print_nbr(flag, prec, ret);
	else
		print_str(flag, prec, string);
}

long long int	convert_nb(va_list ap, char c, char *flag)
{
	long long int	ret;

	if (flag[3] || ft_strindexof("DIOU", flag[4]) != -1)
	{
		if (ft_strindexof("oOuUxX", c) != -1)
			ret = convert_uint(ap, flag[3], flag[4]);
		else
			ret = convert_int(ap, flag[3], flag[4]);
	}
	else
	{
		if (ft_strindexof("di", c) != -1)
			ret = va_arg(ap, int);
		else if (ft_strindexof("ouxX", c) != -1)
			ret = va_arg(ap, unsigned int);
		else
			ret = va_arg(ap, long long);
	}
	return (ret);
}

long long int	convert_uint(va_list ap, char flag1, char flag2)
{
	long long int	ret;

	ret = 0;
	if (flag1 == 'H')
	{
		ret = va_arg(ap, unsigned int);
		if (ret != 65535)
		{
			ret = (unsigned char)ret;
		}
	}
	else if (flag1 == 'l' || ft_isupper(flag2))
		ret = va_arg(ap, unsigned long);
	else if (flag1 == 'h')
		ret = (unsigned short)va_arg(ap, unsigned int);
	else if (flag1 == 'L')
		ret = va_arg(ap, unsigned long long);
	else if (flag1 == 'j')
		ret = va_arg(ap, uintmax_t);
	else
		ret = va_arg(ap, size_t);
	return (ret);
}

long long int	convert_int(va_list ap, char flag1, char flag2)
{
	long long int	ret;

	ret = 0;
	if (flag1 == 'H')
	{
		if (flag2 == 'D')
			ret = va_arg(ap, unsigned long);
		else
		{
			ret = va_arg(ap, int);
			if (ret != 65535)
				ret = (signed char)ret;
		}
	}
	else if (flag1 == 'l' || ft_isupper(flag2))
		ret = va_arg(ap, long);
	else if (flag1 == 'h')
		ret = (short)va_arg(ap, int);
	else if (flag1 == 'L')
		ret = va_arg(ap, long long);
	else if (flag1 == 'j')
		ret = va_arg(ap, uintmax_t);
	else
		ret = va_arg(ap, ssize_t);
	return (ret);
}
