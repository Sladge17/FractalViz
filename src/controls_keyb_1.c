/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyb_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 19:49:03 by student           #+#    #+#             */
/*   Updated: 2020/06/27 19:49:07 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	change_fractal(int keycode, t_sys *sys)
{
	if (select_fractal_1(keycode, sys))
		return (1);
	if (select_fractal_2(keycode, sys))
		return (1);
	if (select_fractal_3(keycode, sys))
		return (1);
	if (select_fractal_4(keycode, sys))
		return (1);
	return (0);
}

char	select_fractal_1(int keycode, t_sys *sys)
{
	if (keycode == 18)
	{
		if (sys->index == 0)
			return (1);
		sys->index = 0;
		sys->str_name = "name: Zulia";
		free(KERNEL);
		KERNEL = clCreateKernel(PROGRAM, "Zulia", NULL);
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	if (keycode == 19)
	{
		if (sys->index == 1)
			return (1);
		sys->index = 1;
		sys->str_name = "name: Mandelbrot";
		free(KERNEL);
		KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	return (0);	
}

char	select_fractal_2(int keycode, t_sys *sys)
{
	if (keycode == 20)
	{
		if (sys->index == 2)
			return (1);
		sys->index = 2;
		sys->str_name = "name: BurningShip";
		free(KERNEL);
		KERNEL = clCreateKernel(PROGRAM, "BurningShip", NULL);
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	if (keycode == 21)
	{
		if (sys->index == 3)
			return (1);
		sys->index = 3;
		sys->str_name = "name: Mandelbar";
		free(KERNEL);
		KERNEL = clCreateKernel(PROGRAM, "Mandelbar", NULL);
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	return (0);
}

char	select_fractal_3(int keycode, t_sys *sys)
{
	if (keycode == 23)
	{
		if (sys->index == 4)
			return (1);
		sys->index = 4;
		sys->str_name = "name: AbsReal";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	if (keycode == 22)
	{
		if (sys->index == 5)
			return (1);
		sys->index = 5;
		sys->str_name = "name: AbsImg";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	return (0);
}

char	select_fractal_4(int keycode, t_sys *sys)
{
	if (keycode == 26)
	{
		if (sys->index == 6)
			return (1);
		sys->index = 6;
		sys->str_name = "name: Power3";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	if (keycode == 28)
	{
		if (sys->index == 7)
			return (1);
		sys->index = 7;
		sys->str_name = "name: AbsRealP4";
		draw_image(sys);
		draw_stat(sys);
		return (1);
	}
	return (0);
}
