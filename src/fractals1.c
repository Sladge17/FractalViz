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

void	calc_zulia(t_sys *sys)
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
				z = add_comp(pow2_comp(z), sys->k[F_ID]);
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_mandelbrot(t_sys *sys)
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
					add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_burningship(t_sys *sys)
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
				z = add_comp(pow2_comp(abs_comp(z)),
					add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_mandelbar(t_sys *sys)
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
				z = add_comp(mbar_comp(z), add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}
