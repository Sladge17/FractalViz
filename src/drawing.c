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

void	draw_winmain(t_sys *sys, int argc, char *argv)
{
	if (argc == 1)
	{
		sys->index = 1;
		sys->name = "name: Mandelbrot";
		set_system(sys);
		clear_image(sys);
		calc_Mandelbrot(sys);
	}
	else
	{
		if (ft_strlen(argv) != 1 || argv[0] < '1' || argv[0] > '8')
			fractol_discr();
		sys->index = ft_atoi(argv) - 1;
		sys->name = set_fractname(sys);
		set_system(sys);
		clear_image(sys);
		calc_fractal(sys);
	}
	WINMAIN = mlx_new_window(MLX, MAIN_W, MAIN_H, "fractol");
	mlx_put_image_to_window(MLX, WINMAIN, IMAGE, 0, 0);
	draw_menu(sys);
	draw_stat(sys);
}

void	draw_image(t_sys *sys)
{
	clear_image(sys);
	calc_fractal(sys);
	if (sys->bitset & 0b00001000)
		draw_axis(sys);
	mlx_put_image_to_window(sys->mlxset->mlx, sys->mlxset->win_main, sys->mlxset->img, 0, 0);
	// mlx_string_put(sys->mlx, sys->win, 0, 0, 0x00FF00, sys->name);
	if (sys->bitset & 0b00001000)
	{
		// NEED OPTIMIZE!!!!!!!!!!!!
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, 5, MAIN_H / 2 - 24, AXIS_C[(int)sys->index], "-real");
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) - 45, MAIN_H / 2 - 24, AXIS_C[(int)sys->index], "real");
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) / 2 + 5, 2, AXIS_C[(int)sys->index], "img");
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) / 2 + 5, MAIN_H - 26, AXIS_C[(int)sys->index], "-img");
	}
}

//// FOR 1920 x 1080
// void	draw_stat(t_sys *sys)
// {
// 	clear_stat(sys);
// 	mlx_put_image_to_window(sys->mlx, sys->win_main, sys->stat, MAIN_W - MENU_W, MAIN_H / 2 + Q);

// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q), TITLE_C, "Statistics");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 40, TEXT_C, "Fractal:");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 65, TEXT_C, sys->name);
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 90, TEXT_C, sys->str_k[(int)sys->index]);
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 115, TEXT_C, sys->str_scale[(int)sys->index]);
	
// 	if (sys->delta[1][(int)sys->index][0] || sys->delta[1][(int)sys->index][1])
// 		mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 140, TEXT_C, "position: shifted");
// 	else
// 		mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 140, TEXT_C, "position: in center");

// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 180, TEXT_C, "Cursor position:");
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 205, TEXT_C, sys->str_cursor[0]);
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 230, TEXT_C, sys->str_cursor[1]);
	
// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 270, TEXT_C, "Scene:");
// 	if (sys->bitset & 0b00001000)
// 		mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 295, TEXT_C, "complex axis: ON");
// 	else
// 		mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 295, TEXT_C, "complex axis: OFF");
// 	if (sys->bitset & 0b00000100)
// 		mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 320, TEXT_C, "isolation mode: ON");
// 	else
// 		mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 320, TEXT_C, "isolation mode: OFF");

// 	mlx_string_put(sys->mlx, sys->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 345, TEXT_C, sys->str_color);
// }

// FOR 1280 x 720
void	draw_stat(t_sys *sys)
{
	clear_stat(sys);
	mlx_put_image_to_window(sys->mlxset->mlx, sys->mlxset->win_main, sys->mlxset->stat, MAIN_W - MENU_W, MAIN_H / 2 + Q);
	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q), TITLE_C, "Statistic");
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 30, TEXT_C, "Fractal");
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 50, TEXT_C, sys->name);
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 70, TEXT_C, sys->str_k[(int)sys->index]);
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 90, TEXT_C, sys->str_scale[(int)sys->index]);
 	if (sys->delta[1][(int)sys->index][0] || sys->delta[1][(int)sys->index][1])
 		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 110, TEXT_C, "position: shifted");
 	else
 		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 110, TEXT_C, "position: in center");
	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 140, TEXT_C, "Cursor position:");
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 160, TEXT_C, sys->str_cursor[0]);
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 180, TEXT_C, sys->str_cursor[1]);
 	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 210, TEXT_C, "Scene:");
 	if (sys->bitset & 0b00001000)
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 230, TEXT_C, "complex axis: ON");
	else
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 230, TEXT_C, "complex axis: OFF");
	if (sys->bitset & 0b00000100)
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 250, TEXT_C, "isolation mode: ON");
	else
		mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 250, TEXT_C, "isolation mode: OFF");
	mlx_string_put(sys->mlxset->mlx, sys->mlxset->win_main, (MAIN_W - MENU_W) + 10, (MAIN_H / 2 + Q) + 270, TEXT_C, sys->str_color);
}



void	draw_fractal(int itr, int i, t_sys *sys)
{
	if (itr == ITER)
	{
		sys->mlxset->imgout[i] = sys->color;
		// if (i - (sys->cursor[0] + (MAIN_W - MENU_W) * sys->cursor[1]) >= 0)
		// 	sys->imgout[i - (sys->cursor[0] + (MAIN_W - MENU_W) * sys->cursor[1])] = sys->color;
		return ;
	}
	if (!(sys->bitset & 0b00000100))
		sys->mlxset->imgout[i] = itr * 1000;
		// if (i - (sys->cursor[0] + (MAIN_W - MENU_W) * sys->cursor[1]) >= 0)
		// 	sys->imgout[i - (sys->cursor[0] + (MAIN_W - MENU_W) * sys->cursor[1])] = itr * 1000;
}

void	draw_axis(t_sys *sys)
{
	int		img_w;
	int		center_h;
	int		i;

	img_w = MAIN_W - MENU_W;
	i = img_w / 2;
	while (i < IMAGE_VOL)
	{
		sys->mlxset->imgout[i] = AXIS_C[(int)sys->index];
		i += img_w;
	}
	
	i = img_w * MAIN_H / 2;
	center_h = i + img_w;
	while (i < center_h)
	{
		sys->mlxset->imgout[i] = AXIS_C[(int)sys->index];
		i += 1;
	}

	int		j;
	int		n;

	i = (MAIN_W - MENU_W) * MAIN_H / 2 + (MAIN_W - MENU_W) / 2 - (MAIN_W - MENU_W) * 3;
	j = 1;
	
	while (i + sys->scale[1][(int)sys->index] * j < i + (MAIN_W - MENU_W) / 2)
	{
		n = 0;
		while(n < 7)
		{
			sys->mlxset->imgout[i + n * (MAIN_W - MENU_W) + sys->scale[1][(int)sys->index] * j] = AXIS_C[(int)sys->index];
			sys->mlxset->imgout[i + n * (MAIN_W - MENU_W) - sys->scale[1][(int)sys->index] * j] = AXIS_C[(int)sys->index];
			n += 1;
		}
		j += 1;
	}

	i = (MAIN_W - MENU_W) * MAIN_H / 2 + (MAIN_W - MENU_W) / 2 - 3;
	j = 1;

	while (i + j * (MAIN_W - MENU_W) * sys->scale[1][(int)sys->index] < IMAGE_VOL)
	{
		n = 0;
		while(n < 7)
		{
			sys->mlxset->imgout[i + (MAIN_W - MENU_W) * sys->scale[1][(int)sys->index] * j + n] = AXIS_C[(int)sys->index];
			sys->mlxset->imgout[i - (MAIN_W - MENU_W) * sys->scale[1][(int)sys->index] * j + n] = AXIS_C[(int)sys->index];
			n += 1;
		}
		j += 1;
	}
}

void	redraw_image(t_sys *sys, int x, int y)
{
	int		color;
	int		i;

	color = sys->mlxset->mnuout[x - (MAIN_W - MENU_W) + MENU_W * y];
	i = 0;
	while (i < IMAGE_VOL)
	{
		if (sys->mlxset->imgout[i] == sys->color)
			sys->mlxset->imgout[i] = color;
		i += 1;
	}
	sys->color = color;
	mlx_put_image_to_window(sys->mlxset->mlx, sys->mlxset->win_main, sys->mlxset->img, 0, 0);
}



















