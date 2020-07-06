/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyb_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 10:48:05 by student           #+#    #+#             */
/*   Updated: 2020/06/06 10:48:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);

char	turn_multythreading(int keycode, t_sys *sys)
{
	if (keycode != 257 && keycode != 258)
		return (0);
	sys->bitset ^= 0b1000000000;
	// if (!(sys->bitset & 0b1000000000))
	// {
	// 	free(KERNEL);
	// 	return (1);
	// }
	// if ((int)sys->index == 0)
	// {
	// 	KERNEL = clCreateKernel(PROGRAM, "Zulia", NULL);
	// 	return (1);
	// }
	// if ((int)sys->index == 1)
	// {
	// 	KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);
	// 	return (1);
	// }
	return (1);
}

char	shift_fractal_k(int keycode, t_sys *sys)
{
	if (check_shiftfractal(keycode, sys))
	{
		shift_fractal(sys);
		return (1);
	}
	if (keycode == 8)
	{
		shift_reset(sys);
		return (1);
	}
	return (0);
}

char	check_shiftfractal(int keycode, t_sys *sys)
{
	if (keycode == 123)
	{
		if (!(sys->bitset & 0b10000000))
			sys->bitset ^= 0b10000000;
		return (1);
	}
	if (keycode == 124)
	{
		if (!(sys->bitset & 0b01000000))
			sys->bitset ^= 0b01000000;
		return (1);
	}
	if (keycode == 126)
	{
		if (!(sys->bitset & 0b00100000))
			sys->bitset ^= 0b00100000;
		return (1);
	}
	if (keycode == 125)
	{
		if (!(sys->bitset & 0b00010000))
			sys->bitset ^= 0b00010000;
		return (1);
	}
	return (0);
}

char	check_unshiftfractal(int keycode, t_sys *sys)
{
	if (keycode == 123)
	{
		sys->bitset ^= 0b10000000;
		return (1);
	}
	if (keycode == 124)
	{
		sys->bitset ^= 0b01000000;
		return (1);
	}
	if (keycode == 126)
	{
		sys->bitset ^= 0b00100000;
		return (1);
	}
	if (keycode == 125)
	{
		sys->bitset ^= 0b00010000;
		return (1);
	}
	return (0);
}

char	scale_fractal_k(int keycode, t_sys *sys)
{
	if (keycode == 12 && sys->cursor[0] >= 0 && sys->cursor[0] < IMAGE_W
		&& sys->cursor[1] >= 0 && sys->cursor[1] < MAIN_H)
	{
		scale_up(sys);
		write_scale(sys);
		return (1);
	}
	if (keycode == 13 && sys->cursor[0] >= 0 && sys->cursor[0] < IMAGE_W
		&& sys->cursor[1] >= 0 && sys->cursor[1] < MAIN_H)
	{
		scale_down(sys);
		write_scale(sys);
		return (1);
	}
	return (0);
}



