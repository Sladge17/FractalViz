/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 09:02:00 by student           #+#    #+#             */
/*   Updated: 2020/05/29 09:02:03 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_comp	init_comp(double real, double img)
{
	t_comp	comp;

	comp.real = real;
	comp.img = img;
	return (comp);
}

t_comp	add_comp(t_comp comp, t_comp comp_add)
{
	comp.real = comp.real + comp_add.real;
	comp.img = comp.img + comp_add.img;
	return (comp);
}

t_comp	mult_comp(t_comp comp_1, t_comp comp_2)
{
	t_comp	comp;

	comp.real = comp_1.real * comp_2.real - comp_1.img * comp_2.img;
	comp.img = comp_1.real * comp_2.img + comp_2.real * comp_1.img;
	return (comp);
}

t_comp	pow2_comp(t_comp comp)
{
	t_comp	comp_pow;

	comp_pow.real = comp.real * comp.real - comp.img * comp.img;
	comp_pow.img = 2 * comp.real * comp.img;
	return (comp_pow);
}

double	len_comp(t_comp comp)
{
	double	len;

	len = sqrt(comp.real * comp.real + comp.img * comp.img);
	return (len);
}

void	scale_comp(t_comp *comp, int scale)
{
	comp->real /= scale;
	comp->img /= scale;

	// comp->real += - (WIDTH - MENU_W) / 2;
	// comp->img /= - (WIDTH - MENU_W) * HEIGHT / 2;
}

t_comp	abs_comp(t_comp comp)
{
	void	*pointer;
	char	i;

	pointer = &comp;
	i = 0;
	while (i < 2)
	{
		if (*(double *)pointer < 0)
			*(double *)pointer *= -1;
		// pointer += 1;
		pointer += sizeof(double);
		i += 1;
	}
	return (comp);
}















