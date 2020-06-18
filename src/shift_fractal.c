/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:07:41 by student           #+#    #+#             */
/*   Updated: 2020/06/06 16:07:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	shift_fractal(t_sys *sys)
{
	unsigned char	shift;

	shift = 0b11110000 & sys->bitset;
	if (ortho_shift(sys, shift))
		return ;
	if (diagonal_shift(sys, shift))
		return ;
	sys->shift[(int)sys->index][0] = 0;
	sys->shift[(int)sys->index][1] = 0;
	draw_image(sys);
}

char	ortho_shift(t_sys *sys, unsigned char shift)
{
	if (shift == 0b10000000)
	{
		shifting_fractal(sys, -1, 0);
		return (1);
	}
	if (shift == 0b01000000)
	{
		shifting_fractal(sys, 1, 0);
		return (1);
	}
	if (shift == 0b00100000)
	{
		shifting_fractal(sys, 0, -1);
		return (1);
	}
	if (shift == 0b00010000)
	{
		shifting_fractal(sys, 0, 1);
		return (1);
	}
	return (0);
}

char	diagonal_shift(t_sys *sys, unsigned char shift)
{
	if (shift == 0b10100000)
	{
		shifting_fractal(sys, -1, -1);
		return (1);
	}
	if (shift == 0b10010000)
	{
		shifting_fractal(sys, -1, 1);
		return (1);
	}
	if (shift == 0b01100000)
	{
		shifting_fractal(sys, 1, -1);
		return (1);
	}
	if (shift == 0b01010000)
	{
		shifting_fractal(sys, 1, 1);
		return (1);
	}
	return (0);
}

void	shifting_fractal(t_sys *sys, char shift_x, char shift_y)
{
	sys->delta0[0] -= sys->delta[0];
	sys->delta0[1] -= sys->delta[1];

	sys->shift[(int)sys->index][0] += shift_x * SHIFT;
	sys->shift[(int)sys->index][1] += shift_y * SHIFT;
	// def_delta(sys);
	draw_image(sys);

	sys->delta0[0] += sys->delta[0];
	sys->delta0[1] += sys->delta[1];
}
