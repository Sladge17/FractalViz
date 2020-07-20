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
	sys->str_scale[F_ID][8] = '\0';
	sys->str_scale[F_ID] = ft_strcat(sys->str_scale[F_ID], "1.000");
	shift_reset(sys);
}
