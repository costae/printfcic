/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:35:02 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:58 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	get_tags(char **fmt, char *flag, int *prec)
{
	(*fmt)++;
	get_flags(fmt, flag);
	if (ft_isdigit(**fmt))
	{
		prec[0] = ft_atoi(*fmt);
		*fmt += nblen(prec[0], 10);
	}
	get_precision(fmt, prec);
	get_length(fmt, flag);
	error_duplicate(fmt, flag, prec);
	flag[4] = **fmt;
	error_tags(flag);
}

void	get_precision(char **fmt, int *prec)
{
	if (**fmt == '.')
	{
		while (**fmt == '.')
			(*fmt)++;
		if (ft_isdigit(*(*(fmt))))
		{
			prec[1] = ft_atoi(*(fmt));
			*fmt += nblen(prec[1], 10);
		}
	}
	else
		prec[1] = -1;
}

void	get_flags(char **fmt, char *flag)
{
	while (**fmt && ft_strindexof("#+- 0", **fmt) != -1)
	{
		if (**fmt == '#' && !flag[0])
			flag[0] = '#';
		if (**fmt == '0' && flag[1] != '-')
			flag[1] = **fmt;
		if (**fmt == '-')
			flag[1] = **fmt;
		if (**fmt == ' ' && !flag[2])
			flag[2] = **fmt;
		if (**fmt == '+')
			flag[2] = **fmt;
		(*fmt)++;
	}
}

void	get_length(char **fmt, char *flag)
{
	while (**fmt && ft_strindexof("hjzl", **fmt) != -1)
	{
		if (**fmt == *(*fmt + 1) || *(*fmt + 1) == 'h')
		{
			if (**fmt == 'h' || **fmt == 'l')
				flag[3] = **fmt - 32;
			else
				flag[3] = 'L';
			(*fmt)++;
		}
		else
			flag[3] = **fmt;
		(*fmt)++;
	}
}
