/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:21:10 by student           #+#    #+#             */
/*   Updated: 2020/06/01 12:21:15 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_image(t_sys *sys)
{
		clear_screen(sys);
		calc_fractal(sys);
		if (sys->bitset & 0b00010000)
			draw_axis(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
}

void	draw_fractal(int itr, int i, t_sys *sys)
{
	if (itr == ITER)
	{
		sys->imgout[i] = FRACT_C;
		return ;
	}
	if (sys->bitset & 0b00001000)
		sys->imgout[i] = itr * 1000;
}

void	draw_axis(t_sys *sys)
{
	int		img_w;
	int		center_h;
	int		i;

	img_w = WIDTH - MENU_W;
	i = img_w / 2;
	while (i < sys->imgvol)
	{
		sys->imgout[i] = AXIS_C;
		i += img_w;
	}
	
	i = img_w * HEIGHT / 2;
	center_h = i + img_w;
	while (i < center_h)
	{
		sys->imgout[i] = AXIS_C;
		i += 1;
	}
}
