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
		mlx_string_put(sys->mlx, sys->win, 0, 0, 0x00FF00, sys->name);
		if (sys->bitset & 0b00010000)
		{
			// NEED OPTIMIZE!!!!!!!!!!!!
			mlx_string_put(sys->mlx, sys->win, 5, HEIGHT / 2 - 24, AXIS_C, "-real");
			mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) - 45, HEIGHT / 2 - 24, AXIS_C, "real");
			mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) / 2 + 5, 2, AXIS_C, "img");
			mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) / 2 + 5, HEIGHT - 26, AXIS_C, "-img");
		}
		// printf("%f %f\n", sys->cursor.real, sys->cursor.img);
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

	int		j;
	int		n;

	i = (WIDTH - MENU_W) * HEIGHT / 2 + (WIDTH - MENU_W) / 2 - (WIDTH - MENU_W) * 3;
	j = 1;
	
	while (i + sys->scale * j < i + (WIDTH - MENU_W) / 2)
	{
		n = 0;
		while(n < 7)
		{
			sys->imgout[i + n * (WIDTH - MENU_W) + sys->scale * j] = AXIS_C;
			sys->imgout[i + n * (WIDTH - MENU_W) - sys->scale * j] = AXIS_C;
			n += 1;
		}
		j += 1;
	}

	i = (WIDTH - MENU_W) * HEIGHT / 2 + (WIDTH - MENU_W) / 2 - 3;
	j = 1;

	while (i + j * (WIDTH - MENU_W) * sys->scale < sys->imgvol)
	{
		n = 0;
		while(n < 7)
		{
			sys->imgout[i + (WIDTH - MENU_W) * sys->scale * j + n] = AXIS_C;
			sys->imgout[i - (WIDTH - MENU_W) * sys->scale * j + n] = AXIS_C;
			n += 1;
		}
		j += 1;
	}
}



















