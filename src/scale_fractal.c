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
	sys->scale[1][F_ID] += ADD_SCALE;
	def_delta(sys);

	if (sys->delta[1][F_ID][0] || sys->delta[1][F_ID][1])
		AXIS_C[F_ID] = AXISK_C;
	else
		AXIS_C[F_ID] = AXISF_C;
	
	draw_image(sys);
}

void	scale_down(t_sys *sys)
{
	if (sys->scale[1][F_ID] == MIN_SCALE)
		return ;
	sys->scale[1][F_ID] -= ADD_SCALE;
	if (sys->scale[1][F_ID] < MIN_SCALE)
		sys->scale[1][F_ID] = MIN_SCALE;
	def_delta(sys);

	if (sys->delta[1][F_ID][0] || sys->delta[1][F_ID][1])
		AXIS_C[F_ID] = AXISK_C;
	else
		AXIS_C[F_ID] = AXISF_C;

	draw_image(sys);	
}

void	scale_reset(t_sys *sys)
{
	sys->scale[0][F_ID] = DEF_SCALE;
	sys->scale[1][F_ID] = DEF_SCALE;
	shift_reset(sys);
	// sys->shift[F_ID][0] = 0;
	// sys->shift[F_ID][1] = 0;
	// sys->delta[0][F_ID][0] = 0;
	// sys->delta[0][F_ID][1] = 0;
	// sys->delta[1][F_ID][0] = 0;
	// sys->delta[1][F_ID][1] = 0;
	// draw_image(sys);
}

void	set_deltazero(t_sys *sys)
{
	sys->delta[0][F_ID][0] = sys->delta[1][F_ID][0] + sys->shift[F_ID][0];
	sys->delta[0][F_ID][1] = sys->delta[1][F_ID][1] + sys->shift[F_ID][1];
	sys->scale[0][F_ID] = sys->scale[1][F_ID];
}
