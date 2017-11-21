/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 18:46:25 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_s(va_list args, t_flags flags)
{
	char	*s;
	int		width;
	size_t 	size;

	(void)flags;
	s = va_arg(args, char*);
	size = ft_strlen(s);
	size = size - (size - flags.precision);
	if (flags.width)
	{
		width = 0;
		while (width++ < flags.width - (int)size)
			write(STDOUT, " ", 1);
	}
	write(STDOUT, s, size);
	return ((int)size + (flags.width - (int)size > 0 ? flags.width - (int)size : 0));
}
