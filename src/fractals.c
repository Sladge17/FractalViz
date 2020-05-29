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

int		calc_Mandelbrot(t_comp z)
{
	int		itr;
	t_comp	c;

	c = z;

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
