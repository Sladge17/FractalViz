/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:34:23 by student           #+#    #+#             */
/*   Updated: 2020/06/22 17:34:26 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	double_to_str(double input, char *str)
{
	int		integer;
	char	sign;
	int		len_int;
	int		len_str;

	if (input < 0)
	{
		sign = 1;
		input = -input;
	}
	else
		sign = 0;
	integer = (int)input;
	len_int = intlen(integer) + sign;
	len_str = len_int + 5;
	write_intpart(str, integer, len_int - 1, sign);
	str[len_int] = '.';
	write_fractpart(str, (int)((input - integer) * 1000), len_str - 2);
	str[len_str - 1] = '\0';
}

int		intlen(int integer)
{
	int		len;

	if (!integer)
		return (1);
	len = 0;
	while (integer)
	{
		len += 1;
		integer /= 10;
	}
	return (len);
}

void	write_intpart(char *str, int integer, int i, char sign)
{
	if (sign)
		str[0] = '-';
	while (i > sign)
	{
		str[i] = (integer % 10) + 48;
		integer /= 10;
		i -= 1;
	}
	str[i] = integer + 48;
}

void	write_fractpart(char *str, int fraction, int i)
{
	int		border;

	border = i - 3;
	while (i > border)
	{
		str[i] = (fraction % 10) + 48;
		fraction /= 10;
		i -= 1;
	}
}
