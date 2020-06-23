/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 10:48:05 by student           #+#    #+#             */
/*   Updated: 2020/06/06 10:48:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	change_fractal(int keycode, t_sys *sys)
{
	if (keycode == 18)
	{
		if (sys->index == 0)
			return (1);
		sys->index = 0;
		sys->name = "name: Zulia";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 19)
	{
		if (sys->index == 1)
			return (1);
		sys->index = 1;
		sys->name = "name: Mandelbrot";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 20)
	{
		if (sys->index == 2)
			return (1);
		sys->index = 2;
		sys->name = "name: BurningShip";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 21)
	{
		if (sys->index == 3)
			return (1);
		sys->index = 3;
		sys->name = "name: Mandelbar";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 23)
	{
		if (sys->index == 4)
			return (1);
		sys->index = 4;
		sys->name = "name: AbsReal";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 22)
	{
		if (sys->index == 5)
			return (1);
		sys->index = 5;
		sys->name = "name: AbsImg";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 26)
	{
		if (sys->index == 6)
			return (1);
		sys->index = 6;
		sys->name = "name: Power3";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}

	if (keycode == 28)
	{
		if (sys->index == 7)
			return (1);
		sys->index = 7;
		sys->name = "name: AbsRealP4";
		draw_image(sys);
		draw_stat(sys);
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



