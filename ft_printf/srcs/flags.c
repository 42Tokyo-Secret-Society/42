/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/26 18:24:08 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

/*
 ** Set everything to 0
*/

void	ft_init_flags(t_flags *flags)
{
	flags->precision = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->hash_key = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->width = 0;
	flags->length_type = 0;
}

/*
 ** Handle flags
 ** Fill t_flags structure and increment the string
**/
int		ft_handle_flags(char **str, t_flags *flags)
{
	if (*(*str) == '-')
	{
		flags->minus = 1;
		(*str)++;
		return (1);
	}
	if (*(*str) == '+')
	{
		flags->plus = 1;
		(*str)++;
		return (1);
	}
	if (*(*str) == ' ')
	{
		flags->space = 1;
		(*str)++;
		return (1);
	}
	if (*(*str) == '0')
	{
		flags->zero = 1;
		(*str)++;
		return (1);
	}
	if (*(*str) == '#')
	{
		flags->hash_key = 1;
		(*str)++;
		return (1);
	}
	return (0);
}

/*
 ** Handle width
 ** (eg. %3d ->   1 || %03d -> 001)
*/
void ft_handle_width(char **str, t_flags *flags, va_list args)
{
	int width;

	if ((width = ft_atoi(*str)) > 0 || **str == '*')
	{
		if (**str == '*')
		{
			width = va_arg(args, int);
			if (width < 0)
				flags->minus = 1;
			flags->width = (width < 0 ? width * -1 : width);
			width = 1;
		}
		else
			flags->width = width;
		while (width > 0 && (*str = *str + 1))
			width /= 10;
	}
}

/*
 ** Handle precision
 ** [.precision]
*/
void ft_handle_precision(char **str, t_flags *flags, va_list args)
{
	int precision;

	if (**str == '.')
	{
		*str += 1;
		if (!ft_isdigit(**str) && **str != '*')
		{
			flags->precision = -1;
			return;
		}
		if (**str == '*')
			precision = va_arg(args, int);
		else
			precision = ft_atoi(*str);
		flags->precision = (precision == 0 ? -1 : precision);
		if (**str == '*')
			precision = 1;
		else if (precision == 0)
			*str += 1;
		while (precision > 0 && (*str = *str + 1))
			precision /= 10;
	}
}

/*
 ** Handle length
*/
void ft_handle_length(char **str, t_flags *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h' && flags->length_type < LENGTH_HH)
	{
		*str += 2;
		flags->length_type = LENGTH_HH;
	}
	else if (**str == 'h' && flags->length_type < LENGTH_H)
	{
		*str += 1;
		flags->length_type = LENGTH_H;
	}
	else if (**str == 'l' && *(*str + 1) == 'l' && flags->length_type < LENGTH_LL)
	{
		*str += 2;
		flags->length_type = LENGTH_LL;
	}
	else if (**str == 'l' && flags->length_type < LENGTH_L)
	{
		*str += 1;
		flags->length_type = LENGTH_L;
	}
	else if (**str == 'j' && flags->length_type < LENGTH_J)
	{
		*str += 1;
		flags->length_type = LENGTH_J;
	}
	else if (**str == 'z' && flags->length_type < LENGTH_Z)
	{
		*str += 1;
		flags->length_type = LENGTH_Z;
	}
}
