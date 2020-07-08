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
		set_system(sys);
		sys->str_name = "name: Mandelbrot";
		KERNEL = clCreateKernel(PROGRAM, "Mandelbrot", NULL);
		calc_Mandelbrot(sys);
	}
	else
	{
		if (ft_strlen(argv) != 1 || argv[0] < '1' || argv[0] > '8')
			fractol_discr();
		sys->index = ft_atoi(argv) - 1;
		set_system(sys);
		set_fractsett(sys);
		calc_fractal(sys);
	}
	WINMAIN = mlx_new_window(MLX, MAIN_W, MAIN_H, "fractol");
	mlx_put_image_to_window(MLX, WINMAIN, IMAGE, 0, 0);
	draw_menu(sys);
	draw_stat(sys);
}

void	draw_image(t_sys *sys)
{
	calc_fractal(sys);
	if (sys->bitset & 0b00001000)
	{
		draw_axis(sys);
		return ;
	}
	mlx_put_image_to_window(MLX, WINMAIN, IMAGE, 0, 0);
}

// FOR 1920 x 1080
void	draw_menu(t_sys *sys)
{
	int		i;

	i = 0;
	while (i < MENU_VOL)
	{
		sys->mlxset->mnuout[i] = MENU_C;
		i += 1;
	}
	sys->rgbtris_y[0] = 325;
	draw_rgbtriangle(sys, MENU_W / 2, 10);
	mlx_put_image_to_window(MLX, WINMAIN, MENU, IMAGE_W, 0);
	mlx_string_put(MLX, WINMAIN, STR_X, 20, TITLE_C, "Main settings");
	mlx_string_put(MLX, WINMAIN, STR_X, 60, STR_C, "1 - 8 - choose fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 100, STR_C, "LMB - transform fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 125, STR_C, "RMB - reset transform");
	mlx_string_put(MLX, WINMAIN, STR_X, 165, STR_C, "SMB - scale fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 190, STR_C, "MMB - reset scale");
	mlx_string_put(MLX, WINMAIN, STR_X, 230, STR_C, "ARROWS - shift fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 255, STR_C, "C - centred fractal");
	mlx_string_put(MLX, WINMAIN, STR_X, 295, STR_C, "Choose fractal color:");
	mlx_string_put(MLX, WINMAIN, STR_X, 550, STR_C, "SPACE - more settings");
}
// // FOR 1280 x 720
// void	draw_menu(t_sys *sys)
// {
// 	int		i;

// 	i = 0;
// 	while (i < MENU_VOL)
// 	{
// 		sys->mlxset->mnuout[i] = MENU_C;
// 		i += 1;
// 	}
// 	sys->rgbtris_y[0] = 245;
// 	draw_rgbtriangle(sys, MENU_W / 2, 40);
// 	mlx_put_image_to_window(MLX, WINMAIN, MENU, IMAGE_W, 0);
// 	mlx_string_put(MLX, WINMAIN, STR_X, 10, TITLE_C, "Main settings");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 40, STR_C, "1 - 8 - choose fractal");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 70, STR_C, "LMB - transform fractal");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 90, STR_C, "RMB - reset transform");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 120, STR_C, "SMB - scale fractal");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 140, STR_C, "MMB - reset scale");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 170, STR_C, "ARROWS - shift fractal");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 190, STR_C, "C - centred fractal");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 220, STR_C, "Choose fractal color:");
// 	mlx_string_put(MLX, WINMAIN, STR_X, 400, STR_C, "SPACE - more settings");
// }

// FOR 1920 x 1080
void	draw_stat(t_sys *sys)
{
	clear_stat(sys);
	mlx_put_image_to_window(MLX, WINMAIN, STAT, IMAGE_W, STAT_Y);
	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y, TITLE_C, "Statistic");
 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 40, STR_C, "Fractal");
 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 65, STR_C, sys->str_name);
 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 90, STR_C, sys->str_k[F_ID]);
 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 115, STR_C,
 		sys->str_scale[F_ID]);
 	if (sys->delta[1][F_ID][0] || sys->delta[1][F_ID][1])
 		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 140, STR_C,
 			"position: shifted");
 	else
 		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 140, STR_C,
 			"position: in center");
	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 180, STR_C,
		"Cursor position:");
 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 205, STR_C,
 		sys->str_cursor[0]);
 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 230, STR_C,
 		sys->str_cursor[1]);
	draw_stat_nest(sys);
}

void	draw_stat_nest(t_sys *sys)
{
	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 270, STR_C, "Scene");
	if (sys->bitset & 0b00000100)
		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 295, STR_C,
			"isolation mode: ON");
	else
		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 295, STR_C,
			"isolation mode: OFF");
	if (sys->bitset & 0b00001000)
		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 320, STR_C,
			"complex axis: ON");
	else
		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 320, STR_C,
			"complex axis: OFF");
	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 345, STR_C, sys->str_color);
	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 385, STR_C, "System");
	if (sys->bitset & 0b1000000000)
		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 410, STR_C,
			"multi-threading: ON");
	else
		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 410, STR_C,
			"multi-threading: OFF");
}



// // FOR 1280 x 720
// void	draw_stat(t_sys *sys)
// {
// 	clear_stat(sys);
// 	mlx_put_image_to_window(MLX, WINMAIN, STAT, IMAGE_W, STAT_Y);
// 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y, TITLE_C, "Statistic");
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 30, STR_C, "Fractal");
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 50, STR_C, sys->str_name);
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 70, STR_C, sys->str_k[F_ID]);
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 90, STR_C, sys->str_scale[F_ID]);
//  	if (sys->delta[1][F_ID][0] || sys->delta[1][F_ID][1])
//  		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 110, STR_C, "position: shifted");
//  	else
//  		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 110, STR_C, "position: in center");
// 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 140, STR_C, "Cursor position:");
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 160, STR_C, sys->str_cursor[0]);
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 180, STR_C, sys->str_cursor[1]);
//  	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 210, STR_C, "Scene:");
//  	if (sys->bitset & 0b00001000)
// 		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 230, STR_C, "complex axis: ON");
// 	else
// 		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 230, STR_C, "complex axis: OFF");
// 	if (sys->bitset & 0b00000100)
// 		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 250, STR_C, "isolation mode: ON");
// 	else
// 		mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 250, STR_C, "isolation mode: OFF");
// 	mlx_string_put(MLX, WINMAIN, STR_X, STAT_Y + 270, STR_C, sys->str_color);
// }

void	redraw_image(t_sys *sys, int x, int y)
{
	int		color;
	int		i;

	color = sys->mlxset->mnuout[x - IMAGE_W + MENU_W * y];
	i = 0;
	while (i < IMAGE_VOL)
	{
		if (sys->mlxset->imgout[i] == sys->color)
			sys->mlxset->imgout[i] = color;
		i += 1;
	}
	sys->color = color;
	mlx_put_image_to_window(MLX, WINMAIN, IMAGE, 0, 0);
	if (sys->bitset & 0b00001000)
		draw_axtitle(sys);
}



















