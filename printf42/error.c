/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmiron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:34:56 by cmiron            #+#    #+#             */
/*   Updated: 2017/02/05 09:35:10 by cmiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	error_tags(char *opt)
{
	if (ft_strindexof("uU", opt[4]) != -1 && opt[2])
		opt[2] = 0;
	if (opt[2] && opt[4] == 'p')
		opt[2] = 0;
	if (opt[2] && (opt[4] == 'o' || opt[4] == 'x' ||
				opt[4] == 'O' || opt[4] == 'X'))
		opt[2] = 0;
}

void	error_duplicate(char **fmt, char *opt, int *plen)
{
	while (ft_strindexof(".#0+ ", *(*fmt)) != -1)
	{
		if (!opt[0] || !opt[1] || !opt[2])
			get_flags(fmt, opt);
		else if (**fmt == '+')
		{
			opt[2] = '+';
			(*fmt)++;
		}
		else
			(*fmt)++;
	}
	if (opt[0] == '#' && opt[1] == '-' && opt[2] == '+')
		plen[1] = 0;
}
