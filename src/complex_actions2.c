/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_actions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 19:36:44 by student           #+#    #+#             */
/*   Updated: 2020/05/31 19:36:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_comp	abs_comp(t_comp comp)
{
	if (comp.real < 0)
		comp.real *= -1;
	if (comp.img < 0)
		comp.img *= -1;
	return (comp);
}

t_comp	absreal_comp(t_comp comp)
{
	if (comp.real < 0)
		comp.real *= -1;
	return (comp);
}

t_comp	absimg_comp(t_comp comp)
{
	if (comp.img < 0)
		comp.img *= -1;
	return (comp);
}

t_comp	mbar_comp(t_comp comp)
{
	t_comp	comp_mbar;

	comp_mbar.real = comp.real * comp.real - comp.img * comp.img;
	comp_mbar.img = comp.real * comp.img * -2;
	return (comp_mbar);
}

double	len_comp(t_comp comp)
{
	double	len;

	len = sqrt(comp.real * comp.real + comp.img * comp.img);
	return (len);
}
