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
	void	*pointer;
	char	i;

	pointer = &comp;
	i = 0;
	while (i < 2)
	{
		if (*(double *)pointer < 0)
			*(double *)pointer *= -1;
		pointer += sizeof(double);
		i += 1;
	}
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

double	len_comp(t_comp comp)
{
	double	len;

	len = sqrt(comp.real * comp.real + comp.img * comp.img);
	return (len);
}

// void	scale_comp(t_comp *comp, t_sys *sys)
// {
// 	comp->real /= sys->scale;
// 	comp->img /= sys->scale;

// 	comp->real += sys->cursor[0];
// 	comp->img += sys->cursor[1];

// 	// comp->real += - (WIDTH - MENU_W) / 2;
// 	// comp->img /= - (WIDTH - MENU_W) * HEIGHT / 2;
// }
