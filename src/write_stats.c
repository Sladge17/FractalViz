/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 09:24:13 by student           #+#    #+#             */
/*   Updated: 2020/06/28 09:24:19 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	write_cursor(t_sys *sys, char drawing)
{
	char	*pointer;
	char	i;

	double_to_str(sys->cursorcomp.real, sys->cursorstr[0]);
	pointer = sys->cursorstr[0];
	i = 7;
	while (*pointer != '\0')
	{
		sys->str_cursor[0][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_cursor[0][(int)i] = '\0';
	double_to_str(sys->cursorcomp.img, sys->cursorstr[1]);
	pointer = sys->cursorstr[1];
	i = 6;
	while (*pointer != '\0')
	{
		sys->str_cursor[1][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_cursor[1][(int)i] = '\0';
	if (drawing)
		draw_stat(sys);
}

void	write_k(t_sys *sys)
{
	char	*pointer;
	char	i;

	pointer = sys->cursorstr[0];
	i = 4;
	while (*pointer != '\0')
	{
		sys->str_k[F_ID][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_k[F_ID][(int)i] = ' ';
	sys->str_k[F_ID][(int)i + 1] = '+';
	sys->str_k[F_ID][(int)i + 2] = ' ';
	i += 3;
	pointer = sys->cursorstr[1];
	while (*pointer != '\0')
	{
		sys->str_k[F_ID][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_k[F_ID][(int)i] = 'i';
	sys->str_k[F_ID][(int)i + 1] = '\0';
	draw_stat(sys);
}

void	write_scale(t_sys *sys)
{
	char	*pointer;
	char	i;

	double_to_str(sys->scale[1][F_ID] / (double)DEF_SCALE, sys->scalestr);
	pointer = sys->scalestr;
	i = 8;
	while (*pointer != '\0')
	{
		sys->str_scale[F_ID][(int)i] = *pointer;
		pointer += 1;
		i += 1;
	}
	sys->str_scale[F_ID][(int)i] = '\0';
	draw_stat(sys);
}

void	write_color(t_sys *sys)
{
	int		dec;
	char	i;

	dec = sys->color;
	i = 20;
	while (dec)
	{
		sys->str_color[(int)i] = sys->hexnumbs[dec % 16];
		dec /= 16;
		i -= 1;
	}
	while (i != 14)
	{
		sys->str_color[(int)i] = '0';
		i -= 1;
	}
	draw_stat(sys);
}

char	*safe_strnew(size_t size)
{
	char	*str;

	if (!(str = ft_strnew(size)))
		exit(0);
	return (str);
}
