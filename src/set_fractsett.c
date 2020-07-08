/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fractsett.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:24:47 by student           #+#    #+#             */
/*   Updated: 2020/07/08 13:24:50 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_fractsett(t_sys *sys)
{
	if (sys->index == 0)
	{
		sys->str_name = "name: Zulia";
		KERNEL = clCreateKernel(PROGRAM, "Zulia", NULL);
		return ;
	}
	if (sys->index == 1)
	{
		sys->str_name = "name: Mandelbrot";
		KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);
		return ;
	}
	if (sys->index == 2)
	{
		sys->str_name = "name: BurningShip";
		KERNEL = clCreateKernel(PROGRAM, "BurningShip", NULL);
		return ;
	}
	if (sys->index == 3)
	{
		sys->str_name = "name: Mandelbar";
		KERNEL = clCreateKernel(PROGRAM, "Mandelbar", NULL);
		return ;
	}
	set_fractsett_nest(sys);
}

void	set_fractsett_nest(t_sys *sys)
{
	if (sys->index == 4)
	{
		sys->str_name = "name: AbsReal";
		KERNEL = clCreateKernel(PROGRAM, "AbsReal", NULL);
		return ;
	}
	if (sys->index == 5)
	{
		sys->str_name = "name: AbsImg";
		KERNEL = clCreateKernel(PROGRAM, "AbsImg", NULL);
		return ;
	}
	if (sys->index == 6)
	{
		sys->str_name = "name: Power3";
		KERNEL = clCreateKernel(PROGRAM, "Power3", NULL);
		return ;
	}
	sys->str_name = "name: AbsRealP4";
	KERNEL = clCreateKernel(PROGRAM, "AbsRealP4", NULL);
}
