/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_actions1.c                                 :+:      :+:    :+:   */
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

t_comp	ppow_comp(t_comp comp, int power)
{
	int		i;
	t_comp	tmp;

	if (!power)
		return (init_comp(1, 0));
	tmp = comp;
	i = 1;
	while (i < power)
	{
		comp = mult_comp(comp, tmp);
		i += 1;
	}
	return (comp);
}
