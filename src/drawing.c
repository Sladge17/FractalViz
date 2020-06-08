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
	clear_image(sys);
	calc_fractal(sys);
	if (sys->bitset & 0b00001000)
		draw_axis(sys);
	mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
	// mlx_string_put(sys->mlx, sys->win, 0, 0, 0x00FF00, sys->name);
	if (sys->bitset & 0b00001000)
	{
		// NEED OPTIMIZE!!!!!!!!!!!!
		mlx_string_put(sys->mlx, sys->win, 5, HEIGHT / 2 - 24, AXIS_C, "-real");
		mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) - 45, HEIGHT / 2 - 24, AXIS_C, "real");
		mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) / 2 + 5, 2, AXIS_C, "img");
		mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) / 2 + 5, HEIGHT - 26, AXIS_C, "-img");
	}
}

void	draw_stat(t_sys *sys)
{
	clear_stat(sys);
	mlx_put_image_to_window(sys->mlx, sys->win, sys->stat, WIDTH - MENU_W, HEIGHT / 2);
	mlx_string_put(sys->mlx, sys->win, (WIDTH - MENU_W) + 10, (HEIGHT / 2) + 10, 0x00FF00, sys->name);
	// printf("%f %f\n", sys->cursorcomp.real, sys->cursorcomp.img);
	printf("%d %d\n", sys->cursor[0], sys->cursor[1]);
}

void	draw_fractal(int itr, int i, t_sys *sys)
{
	if (itr == ITER)
	{
		sys->imgout[i] = sys->color;
		// if (i - (sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1]) >= 0)
		// 	sys->imgout[i - (sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1])] = sys->color;
		return ;
	}
	if (sys->bitset & 0b00000100)
		sys->imgout[i] = itr * 1000;
		// if (i - (sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1]) >= 0)
		// 	sys->imgout[i - (sys->cursor[0] + (WIDTH - MENU_W) * sys->cursor[1])] = itr * 1000;
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

void	redraw_image(t_sys *sys, int x, int y)
{
	int		color;
	int		i;

	color = sys->mnuout[x - (WIDTH - MENU_W) + MENU_W * y];
	i = 0;
	while (i < sys->imgvol)
	{
		if (sys->imgout[i] == sys->color)
			sys->imgout[i] = color;
		i += 1;
	}
	sys->color = color;
	mlx_put_image_to_window(sys->mlx, sys->win, sys->img, 0, 0);
}



















