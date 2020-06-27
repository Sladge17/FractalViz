/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 19:26:09 by student           #+#    #+#             */
/*   Updated: 2020/05/31 19:26:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_AbsReal(t_sys *sys)
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
			z = add_comp(pow2_comp(absreal_comp(z)),
				add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_AbsImg(t_sys *sys)
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
			z = add_comp(pow2_comp(absimg_comp(z)),
				add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_Power3(t_sys *sys)
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
				z = add_comp(ppow_comp(z, 3), sys->k[F_ID]);
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}

void	calc_AbsRealP4(t_sys *sys)
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
			z = add_comp(ppow_comp(absreal_comp(z), 4),
				add_comp(c, sys->k[F_ID]));
			if (len_comp(z) > 4)
				break ;
			itr += 1;
		}
		draw_fractal(itr, i, sys);
		i += 1;
	}
}
