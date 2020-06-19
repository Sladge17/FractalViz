/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:15:25 by student           #+#    #+#             */
/*   Updated: 2020/06/19 14:15:29 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scale_up(t_sys *sys)
{
	sys->scale[1][(int)sys->index] += ADD_SCALE;
	def_delta(sys);
	draw_image(sys);
}

void	scale_down(t_sys *sys)
{
	if (sys->scale[1][(int)sys->index] == MIN_SCALE)
		return ;
	sys->scale[1][(int)sys->index] -= ADD_SCALE;
	if (sys->scale[1][(int)sys->index] < MIN_SCALE)
		sys->scale[1][(int)sys->index] = MIN_SCALE;
	def_delta(sys);
	draw_image(sys);	
}

void	scale_reset(t_sys *sys)
{
	sys->scale[0][(int)sys->index] = DEF_SCALE;
	sys->scale[1][(int)sys->index] = DEF_SCALE;
	shift_reset(sys);
	// sys->shift[(int)sys->index][0] = 0;
	// sys->shift[(int)sys->index][1] = 0;
	// sys->delta[0][(int)sys->index][0] = 0;
	// sys->delta[0][(int)sys->index][1] = 0;
	// sys->delta[1][(int)sys->index][0] = 0;
	// sys->delta[1][(int)sys->index][1] = 0;
	// draw_image(sys);
}

void	set_deltazero(t_sys *sys)
{
	sys->delta[0][(int)sys->index][0] = sys->delta[1][(int)sys->index][0] + sys->shift[(int)sys->index][0];
	sys->delta[0][(int)sys->index][1] = sys->delta[1][(int)sys->index][1] + sys->shift[(int)sys->index][1];
	sys->scale[0][(int)sys->index] = sys->scale[1][(int)sys->index];
}
