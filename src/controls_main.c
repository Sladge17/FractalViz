/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:25:51 by student           #+#    #+#             */
/*   Updated: 2020/05/28 09:25:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int keycode, void *param)
{
	t_sys		*sys;

	sys = (t_sys *)param;

	if (keycode == 53)
		exit(0);

	if (keycode == 12)
	{
		sys->scale += 10;
		fill_screen(sys);
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	}

	if (keycode == 13)
	{
		if (!sys->scale)
			return (0);
		fill_screen(sys);
		sys->scale -= 10;
		if (sys->scale <= 0)
		{
			sys->scale = 0;
			sys->imgout[sys->imgvol / 2 + (WIDTH - MENU_W) / 2] = 0xFF0000;
			mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
			return (0);
		}
		calc_fractal(sys);
		mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	}

	return (0);
}
