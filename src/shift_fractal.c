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
	if (shift_ortho(sys, shift))
		return ;
	if (shift_diagonal(sys, shift))
		return ;
	shift_reset(sys);
	// sys->shift[(int)sys->index][0] = 0;
	// sys->shift[(int)sys->index][1] = 0;
	// sys->delta[0][(int)sys->index][0] = 0;
	// sys->delta[0][(int)sys->index][1] = 0;
	// sys->delta[1][(int)sys->index][0] = 0;
	// sys->delta[1][(int)sys->index][1] = 0;
	// draw_image(sys);
}

char	shift_ortho(t_sys *sys, unsigned char shift)
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

char	shift_diagonal(t_sys *sys, unsigned char shift)
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
	// sys->delta0[0] -= sys->delta[0];
	// sys->delta0[1] -= sys->delta[1];

	sys->shift[(int)sys->index][0] += shift_x * SHIFT;
	sys->shift[(int)sys->index][1] += shift_y * SHIFT;
	// AXIS_C[(int)sys->index] = AXISK_C;
	def_delta(sys);
	if (!sys->delta[1][(int)sys->index][0] && !sys->delta[1][(int)sys->index][1])
		AXIS_C[(int)sys->index] = AXISF_C;
	else
		AXIS_C[(int)sys->index] = AXISK_C;
	draw_image(sys);
	draw_stat(sys);

	// sys->delta0[0] += sys->delta[0];
	// sys->delta0[1] += sys->delta[1];
}

void	shift_reset(t_sys *sys)
{
	sys->shift[(int)sys->index][0] = 0;
	sys->shift[(int)sys->index][1] = 0;
	sys->delta[0][(int)sys->index][0] = 0;
	sys->delta[0][(int)sys->index][1] = 0;
	sys->delta[1][(int)sys->index][0] = 0;
	sys->delta[1][(int)sys->index][1] = 0;
	AXIS_C[(int)sys->index] = AXISF_C;
	draw_image(sys);
	draw_stat(sys);
}












