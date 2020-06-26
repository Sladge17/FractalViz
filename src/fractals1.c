/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:19:37 by student           #+#    #+#             */
/*   Updated: 2020/05/29 16:19:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_Zulia(t_sys *sys)
{
	int		i;
	t_comp	z;
	int		itr;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		itr = 0;
		while (itr < ITER)
		{
			if (itr)
				z = add_comp(pow2_comp(z), sys->k[(int)sys->index]);
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_Mandelbrot(t_sys *sys)
{
	int		i;
	t_comp	z;
	t_comp	c;
	int		itr;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		c = z;
		itr = 0;
		while (itr < ITER)
		{
			if (itr)
				z = add_comp(pow2_comp(z),
					add_comp(c, sys->k[(int)sys->index]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_BurningShip(t_sys *sys)
{
	int		i;
	t_comp	z;
	t_comp	c;
	int		itr;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		c = z;
		itr = 0;
		while (itr < ITER)
		{
			z = add_comp(pow2_comp(abs_comp(z)),
				add_comp(c, sys->k[(int)sys->index]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_Mandelbar(t_sys *sys)
{
	int		i;
	t_comp	z;
	t_comp	c;
	int		itr;
	t_comp	tmp_z;

	i = 0;
	while (i < IMAGE_VOL)
	{
		z = int_to_comp(sys, i);
		c = z;
		itr = 0;
		while (itr < ITER)
		{
			tmp_z.real = z.real * z.real - z.img * z.img;
			tmp_z.img = z.real * z.img * -2;
			z = add_comp(tmp_z, add_comp(c, sys->k[(int)sys->index]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}
