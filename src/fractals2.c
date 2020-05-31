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

int		calc_Power3(t_comp z, t_comp c)
{
	int		itr;

	itr = 0;
	while (itr < ITER)
	{
		if (itr)
			z = add_comp(ppow_comp(z, 3), c);
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}

int		calc_AbsRealP4(t_comp z, t_comp k)
{
	int		itr;
	t_comp	c;

	c = z;
	itr = 0;
	while (itr < ITER)
	{
		z = add_comp(ppow_comp(absreal_comp(z), 4), add_comp(c, k));
		if (len_comp(z) > 4)
			return (itr);
		itr += 1;
	}
	return (itr);
}
