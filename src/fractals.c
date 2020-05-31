/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:19:37 by student           #+#    #+#             */
/*   Updated: 2020/05/29 16:19:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		calc_Zulia(t_comp z, t_comp c)
{
	int		itr;

	itr = 0;
	while (itr < ITER)
	{
		if (itr)
			z = add_comp(pow2_comp(z), c);
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}

int		calc_Mandelbrot(t_comp z, t_comp k)
{
	int		itr;
	t_comp	c;

	c = z;
	itr = 0;
	while (itr < ITER)
	{
		if (itr)
			z = add_comp(pow2_comp(z), add_comp(c, k));
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}

int		calc_BurningShip(t_comp z, t_comp k)
{
	int		itr;
	t_comp	c;

	c = z;
	itr = 0;
	while (itr < ITER)
	{
		z = add_comp(pow2_comp(abs_comp(z)), add_comp(c, k));
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}

int		calc_Mandelbar(t_comp z, t_comp k)
{
	int		itr;
	t_comp	c;
	t_comp	tmp_z;

	c = z;
	itr = 0;
	while (itr < ITER)
	{
		tmp_z.real = z.real * z.real - z.img * z.img;
		tmp_z.img = z.real * z.img * -2;
		z = add_comp(tmp_z, add_comp(c, k));
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}

int		calc_AbsReal(t_comp z, t_comp k)
{
	int		itr;
	t_comp	c;

	c = z;
	itr = 0;
	while (itr < ITER)
	{
		z = add_comp(pow2_comp(absreal_comp(z)), add_comp(c, k));
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}

int		calc_AbsImg(t_comp z, t_comp k)
{
	int		itr;
	t_comp	c;

	c = z;
	itr = 0;
	while (itr < ITER)
	{
		z = add_comp(pow2_comp(absimg_comp(z)), add_comp(c, k));
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}























